#include "SDL.h"
#include "Geometry.h"
#include "Calculations.h"
#include <iostream>
#include <vector>

float degToRad(float deg) {
	return deg * (M_PI / 180);
}

float radToDeg(float rad) {
	return rad * (180 / M_PI);
}

float sign(SDL_Point p1, SDL_Point p2, SDL_Point p3) {
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

float sign(SDL_Point p1, SDL_Vertex* v1, SDL_Vertex* v2) {
	return (p1.x - v2->position.x) * (v1->position.y - v2->position.y) - (v1->position.x - v2->position.x) * (p1.y - v2->position.y);
}

bool inTriangle(Triangle* tri, SDL_Point* p) {
	float d1, d2, d3;
	bool hasNeg, hasPos;

	SDL_Point localPoint = PointToLocalSpace(tri->o, p,  -(tri->rotation));

	d1 = sign(localPoint, tri->v1, tri->v2);
	d2 = sign(localPoint, tri->v2, tri->v3);
	d3 = sign(localPoint, tri->v3, tri->v1);

	hasNeg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	hasPos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(hasNeg && hasPos);
}

SDL_Point RotatePoint(SDL_Point point, float angle) {
	float c = cos(angle);
	float s = sin(angle);

	int xNew = c * point.x - s * point.y;
	int yNew = s * point.x + c * point.y;

	point.x = xNew;
	point.y = yNew;

	return point;
}

SDL_Point RotatePoint(SDL_Point* point, float angle) {
	SDL_Point rotatedPoint;

	float c = cos(angle);
	float s = sin(angle);

	rotatedPoint.x = c * point->x - s * point->y;
	rotatedPoint.y = s * point->x + c * point->y;

	return rotatedPoint;
}

SDL_Vertex RotatePoint(SDL_Vertex* vertex, float angle) {
	SDL_Vertex rotatedPoint = *(vertex);

	float c = cos(angle);
	float s = sin(angle);

	rotatedPoint.position.x = c * vertex->position.x - s * vertex->position.y;
	rotatedPoint.position.y = s * vertex->position.x + c * vertex->position.y;

	return rotatedPoint;
}

SDL_Point PointToLocalSpace(SDL_Point* origin, SDL_Point* point) {
	SDL_Point localPoint;
	localPoint.x = point->x - origin->x;
	localPoint.y = point->y - origin->y;
	return localPoint;
}

SDL_Point PointToLocalSpace(SDL_Point* origin, SDL_Point* point, float angle) {
	SDL_Point localPoint = PointToLocalSpace(origin, point);
	localPoint = RotatePoint(localPoint, angle);

	return localPoint;
}

SDL_Point PointToWorldSpace(SDL_Point* origin, SDL_Point* point) {
	SDL_Point worldPoint;
	worldPoint.x = point->x + origin->x;
	worldPoint.y = point->y + origin->y;
	return worldPoint;
}

SDL_Vertex PointToLocalSpace(SDL_Point* origin, SDL_Vertex* vertex) {
	SDL_Vertex localPoint = *vertex;
	localPoint.position.x = vertex->position.x - origin->x;
	localPoint.position.y = vertex->position.y - origin->y;
	return localPoint;
}

SDL_Vertex PointToLocalSpace(SDL_Point* origin, SDL_Vertex* vertex, float angle) {
	SDL_Vertex localPoint = PointToLocalSpace(origin, vertex);
	localPoint = RotatePoint(&localPoint, angle);

	return localPoint;
}

SDL_Vertex PointToWorldSpace(SDL_Point* origin, SDL_Vertex vertex) {
	SDL_Vertex worldPoint = vertex;
	worldPoint.position.x = vertex.position.x + origin->x;
	worldPoint.position.y = vertex.position.y + origin->y;
	return worldPoint;
}

void drawTriangle(Triangle* tri, SDL_Renderer* renderer) {
	SDL_RenderGeometry(renderer, nullptr, tri->getVertices(), 3, nullptr, 0);
}

void drawRectangle(Rectangle* rect, SDL_Renderer* renderer) {
	Triangle t1(rect->o.x, rect->o.y, rect->v1, rect->v2, rect->v3);
	Triangle t2(rect->o.x, rect->o.y, rect->v2, rect->v3, rect->v4);

	t1.rotate(rect->rotation);
	t2.rotate(rect->rotation);

	drawTriangle(&t1, renderer);
	drawTriangle(&t2, renderer);
}

void drawCircle(Circle* circ, SDL_Renderer* renderer, int precision) {

	float angle = 360 / precision;
	SDL_Vertex reference = { {-(circ->radius), 0}, {255, 0, 0, 255}, {1,1} };
	SDL_Vertex origin = { {0, 0}, {255, 0, 0, 255}, {1, 1} };

	for (float i = 0.0; i < 360.0; i += angle) {
		SDL_Vertex rotatedPoint = RotatePoint(&reference, degToRad(angle));
		Triangle slice(circ->o.x, circ->o.y, &origin, &reference, &rotatedPoint);
		drawTriangle(&slice, renderer);
		reference = rotatedPoint;
	}
	
}

void drawShape(Shape* shape, SDL_Renderer* renderer) {
	for (int i = 0; i < shape->triangles.size(); i++) {
		Triangle* currentTriangle = &(shape->triangles[i]);
		drawTriangle(currentTriangle, renderer);
	}
}

void setTriangleColor(Triangle* t, SDL_Color c) {
	t->v1->color = c;
	t->v2->color = c;
	t->v3->color = c;
}

void setShapeColor(Shape* s, SDL_Color c) {
	for (int i = 0; i < s->triangles.size(); i++) {
		setTriangleColor(&(s->triangles[i]), c);
	}
}

Triangle* getRectangleRepresentation(Rectangle* rect) {
	Triangle t1(rect->o.x, rect->o.y, rect->v1, rect->v2, rect->v3);
	Triangle t2(rect->o.x, rect->o.y, rect->v2, rect->v3, rect->v4);

	t1.rotate(rect->rotation);
	t2.rotate(rect->rotation);

	return new Triangle[2]{ t1, t2 };
}

std::vector<Triangle> getCircleRepresentation(Circle* circ, int precision) {
	float angle = 360 / precision;
	SDL_Vertex reference = { {-(circ->radius), 0}, {255, 0, 0, 255}, {1, 1} };
	SDL_Vertex origin = { {0, 0}, {255, 0, 0, 255}, {1, 1} };

	std::vector<Triangle> triangles;

	for (float i = 0.0; i < 360.0; i += angle) {
		SDL_Vertex rotatedPoint = RotatePoint(&reference, degToRad(angle)) ;
		Triangle slice(circ->o.x, circ->o.y, &origin, &reference, &rotatedPoint);
		triangles.push_back(slice);
		reference = rotatedPoint;
	}
	return triangles;
}
