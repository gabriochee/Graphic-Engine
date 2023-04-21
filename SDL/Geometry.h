#pragma once

class Triangle {
public:
	SDL_Point* o, * v1, * v2, * v3; // o = origin, vN = vertice number N
	SDL_Point* vertices = new SDL_Point[3];
	float rotation = 0;

	Triangle(int x, int y);
	Triangle(int x, int y, int v1x, int v1y, int v2x, int v2y, int v3x, int v3y);
	Triangle(int x, int y, SDL_Point* vp1, SDL_Point* vp2, SDL_Point* vp3);

	~Triangle();

	SDL_Point* getVertices();

	void rotate(float angle);

};

class Rectangle {
public:
	SDL_Point o, v1, v2, v3, v4;
	int width, height;
	float rotation = 0;

	Rectangle(int x, int y, int w, int h);
	Rectangle(SDL_Point* origin, int w, int h);

	void rotate(float angle);

};
