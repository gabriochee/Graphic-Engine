#include "SDL.h"
#include "Geometry.h"
#include "Calculations.h"
#include <iostream>

float degToRad(float deg) {
	return deg * (M_PI / 180);
}

float radToDeg(float rad) {
	return rad * (180 / M_PI);
}

float sign(SDL_Point p1, SDL_Point p2, SDL_Point p3) {
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

int* getTriangleEnds(Triangle* tri) {
	int* ends = new int[4];
	SDL_Point* vertices = new SDL_Point[3];

	vertices[0] = *(tri->v1);
	vertices[1] = *(tri->v2);
	vertices[2] = *(tri->v3);

	for (int i = 0; i < 3; i++) {
		vertices[i] = RotatePoint(vertices[i], tri->rotation);
	}

	SDL_Point min_x, max_x, min_y, max_y;
	min_x = max_x = vertices[0];
	min_y = max_y = vertices[0];
	for (int i = 1; i <= 2; i++) {
		if (vertices[i].x < min_x.x) {
			min_x = vertices[i];
		}
		else if (vertices[i].x > max_x.x) {
			max_x = vertices[i];
		}
		if (vertices[i].y < min_y.y) {
			min_y = vertices[i];
		} 
		else if (vertices[i].y > max_y.y) {
			max_y = vertices[i];
		}
	}


	delete[] vertices;

	ends[0] = PointToWorldSpace(tri->o, &min_x).x;
	ends[1] = PointToWorldSpace(tri->o, &max_x).x;
	ends[2] = PointToWorldSpace(tri->o, &min_y).y;
	ends[3] = PointToWorldSpace(tri->o, &max_y).y;

	return ends;
}

bool inTriangle(Triangle* tri, SDL_Point* p) {
	float d1, d2, d3;
	bool hasNeg, hasPos;

	SDL_Point localPoint = PointToLocalSpace(tri->o, p,  -(tri->rotation));

	d1 = sign(localPoint, *(tri->v1), *(tri->v2));
	d2 = sign(localPoint, *(tri->v2), *(tri->v3));
	d3 = sign(localPoint, *(tri->v3), *(tri->v1));

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

SDL_Point RotateFromPoint(SDL_Point* pivot, SDL_Point point, float angle) {
	SDL_Point transformed;
	transformed.x = point.x - pivot->x;
	transformed.y = point.y - pivot->y;

	float c = cos(angle);
	float s = sin(angle);

	int xNew = c * transformed.x - s * transformed.y;
	int yNew = s * transformed.x + c * transformed.y;

	transformed.x = xNew + pivot->x;
	transformed.y = yNew + pivot->y;

	return transformed;
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

void drawTriangle(Triangle* tri, SDL_Renderer* renderer) {
	SDL_Point* vertices = tri->getVertices();

	SDL_RenderDrawLine(renderer, vertices[0].x, vertices[0].y, vertices[1].x, vertices[1].y);
	SDL_RenderDrawLine(renderer, vertices[0].x, vertices[0].y, vertices[2].x, vertices[2].y);
	SDL_RenderDrawLine(renderer, vertices[1].x, vertices[1].y, vertices[2].x, vertices[2].y);
}

void fillTriangle(Triangle* tri, SDL_Renderer* renderer) {
	drawTriangle(tri, renderer);

	int* ends = getTriangleEnds(tri);

	for (int i = ends[0]; i < ends[1]; i++) {
		for (int j = ends[2]; j < ends[3]; j++) {
			SDL_Point pixel;
			pixel.x = i;
			pixel.y = j;
			if (inTriangle(tri, &pixel)) {
				SDL_RenderDrawPoint(renderer, i, j);
			}
		}
	}
	delete[] ends;
}

void drawRectangle(Rectangle* rect, SDL_Renderer* renderer) {
	Triangle t1(rect->o.x, rect->o.y, &(rect->v1), &(rect->v2), &(rect->v3));
	Triangle t2(rect->o.x, rect->o.y, &(rect->v2), &(rect->v3), &(rect->v4));

	t1.rotate(rect->rotation);
	t2.rotate(rect->rotation);

	drawTriangle(&t1, renderer);
	drawTriangle(&t2, renderer);
}

void fillRectangle(Rectangle* rect, SDL_Renderer* renderer) {
	Triangle t1(rect->o.x, rect->o.y, &(rect->v1), &(rect->v2), &(rect->v3));
	Triangle t2(rect->o.x, rect->o.y, &(rect->v2), &(rect->v3), &(rect->v4));

	t1.rotate(rect->rotation);
	t2.rotate(rect->rotation);

	fillTriangle(&t1, renderer);
	fillTriangle(&t2, renderer);
}
