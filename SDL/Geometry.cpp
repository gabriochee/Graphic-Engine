#include "SDL.h"
#include "Geometry.h"
#include "Calculations.h"
#include <iostream>
#include <vector>

Triangle::Triangle() {
	o = new SDL_Point;

	o->x = 0;
	o->y = 0;
}

Triangle::Triangle(int x, int y) {
	
	o = new SDL_Point;
	v1 = new SDL_Vertex;
	v2 = new SDL_Vertex;
	v3 = new SDL_Vertex;

	o->x = x;
	o->y = y;

	v1->position.x = 0;
	v1->position.y = 0;

	v2->position.x = 0;
	v2->position.y = 0;

	v3->position.x = 0;
	v3->position.y = 0;
}

Triangle::Triangle(int x, int y, int v1x, int v1y, int v2x, int v2y, int v3x, int v3y) {

	o = new SDL_Point;
	v1 = new SDL_Vertex;
	v2 = new SDL_Vertex;
	v3 = new SDL_Vertex;

	o->x = x;
	o->y = y;

	v1->position.x = v1x;
	v1->position.y = v1y;

	v2->position.x = v2x;
	v2->position.y = v2y;

	v3->position.x = v3x;
	v3->position.y = v3y;
}

Triangle::Triangle(int x, int y, SDL_Vertex* vp1, SDL_Vertex* vp2, SDL_Vertex* vp3) {

	o = new SDL_Point;

	o->x = x;
	o->y = y;

	v1 = vp1;
	v2 = vp2;
	v3 = vp3;
}

void Triangle::rotate(float angle) {
	rotation += angle;
}

const SDL_Vertex* Triangle::getVertices() {
	SDL_Vertex vw1, vw2, vw3;

	vw1 = PointToWorldSpace(o, RotatePoint(v1, rotation));
	vw2 = PointToWorldSpace(o, RotatePoint(v2, rotation));
	vw3 = PointToWorldSpace(o, RotatePoint(v3, rotation));

	const SDL_Vertex vertices[] = {
		vw1,
		vw2,
		vw3
	};
	
	return vertices;
}

Rectangle::Rectangle(int x, int y, int w, int h) {
	width = w;
	height = h;

	o.x = x;
	o.y = y;

	v1 = new SDL_Vertex;
	v2 = new SDL_Vertex;
	v3 = new SDL_Vertex;
	v4 = new SDL_Vertex;

	v1->position.x = -(width / 2);
	v1->position.y = -(height / 2);

	v2->position.x = width / 2;
	v2->position.y = -(height / 2);

	v3->position.x = -(width / 2);
	v3->position.y = height / 2;

	v4->position.x = width / 2;
	v4->position.y = height / 2;

}

void Rectangle::rotate(float angle) {
	rotation += angle;
}

void Rectangle::setColor(SDL_Color color) {
	v1->color = color;
	v2->color = color;
	v3->color = color;
	v4->color = color;
}

Circle::Circle(int x, int y, float r) {
	o.x = x;
	o.y = y;

	radius = r;
}

Shape::Shape(int x, int y) {
	o.x = x;
	o.y = y;
}

Shape::Shape(int x, int y, Triangle* triangleSet, int triangleNum) {
	o.x = x;
	o.y = y;

	for (int i = 0; i < triangleNum; i++) {
		triangles.push_back(triangleSet[i]);
	}
	delete[] triangleSet;
}

void Shape::addTriangle(Triangle t) {
	triangles.push_back(t);
}

void Shape::addTriangle(std::vector<Triangle> triangleSet) {
	triangles.insert(std::end(triangles), std::begin(triangleSet), std::end(triangleSet));
}

Triangle* Shape::getTriangles() {
	return triangles.data();
}
