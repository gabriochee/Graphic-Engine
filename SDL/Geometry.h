#pragma once
#include <vector>

struct Triangle {
	SDL_Point* o; // o = origin
	SDL_Vertex *v1, *v2, *v3; // vN = vertex number N
	float rotation = 0;

	Triangle();
	Triangle(int x, int y);
	Triangle(int x, int y, int v1x, int v1y, int v2x, int v2y, int v3x, int v3y);
	Triangle(int x, int y, SDL_Vertex* vp1, SDL_Vertex* vp2, SDL_Vertex* vp3);

	const SDL_Vertex* getVertices();

	void rotate(float angle);

};

struct Rectangle {
	SDL_Point o;
	SDL_Vertex *v1, *v2, *v3, *v4;
	int width, height;
	float rotation = 0;

	Rectangle(int x, int y, int w, int h);

	void rotate(float angle);
	void setColor(SDL_Color color);

};

struct Circle {
	SDL_Point o;
	float radius = 0;

	Circle(int x, int y, float r);

};

struct Shape {
	SDL_Point o;
	std::vector<Triangle> triangles;

	Shape(int x, int y);
	Shape(int x, int y, Triangle* triangleSet, int triangleNum);

	void addTriangle(Triangle t);
	void addTriangle(std::vector<Triangle> triangles);
	Triangle* getTriangles();
};
