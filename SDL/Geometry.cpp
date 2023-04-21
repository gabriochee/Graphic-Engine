#include "SDL.h"
#include "Geometry.h"
#include "Calculations.h"

Triangle::Triangle(int x, int y) {
	
	o = new SDL_Point;
	v1 = new SDL_Point;
	v2 = new SDL_Point;
	v3 = new SDL_Point;

	o->x = x;
	o->y = y;

	v1->x = 0;
	v1->y = 0;

	v2->x = 0;
	v2->y = 0;

	v3->x = 0;
	v3->y = 0;
}

Triangle::Triangle(int x, int y, int v1x, int v1y, int v2x, int v2y, int v3x, int v3y) {

	o = new SDL_Point;
	v1 = new SDL_Point;
	v2 = new SDL_Point;
	v3 = new SDL_Point;

	o->x = x;
	o->y = y;

	v1->x = v1x;
	v1->y = v1y;

	v2->x = v2x;
	v2->y = v2y;

	v3->x = v3x;
	v3->y = v3y;
}

Triangle::Triangle(int x, int y, SDL_Point* vp1, SDL_Point* vp2, SDL_Point* vp3) {

	o = new SDL_Point;

	o->x = x;
	o->y = y;

	v1 = vp1;
	v2 = vp2;
	v3 = vp3;
}

Triangle::~Triangle() {
	delete[] vertices;
	delete o, v1, v2, v3;
}

void Triangle::rotate(float angle) {
	rotation = angle;
}

SDL_Point* Triangle::getVertices() {

	vertices[0] = RotatePoint(v1, rotation);
	vertices[1] = RotatePoint(v2, rotation);
	vertices[2] = RotatePoint(v3, rotation);

	vertices[0] = PointToWorldSpace(o, &vertices[0]);
	vertices[1] = PointToWorldSpace(o, &vertices[1]);
	vertices[2] = PointToWorldSpace(o, &vertices[2]);

	return vertices;
}

Rectangle::Rectangle(int x, int y, int w, int h) {
	width = w;
	height = h;

	o.x = x;
	o.y = y;

	v1.x = -(width / 2);
	v1.y = -(height / 2);

	v2.x = width / 2;
	v2.y = -(height / 2);

	v3.x = -(width / 2);
	v3.y = height / 2;

	v4.x = width / 2;
	v4.y = height / 2;

}

Rectangle::Rectangle(SDL_Point* origin, int w, int h) {
	Rectangle::Rectangle(origin->x, origin->y, w, h);
}

void Rectangle::rotate(float angle) {
	rotation = angle;
}
