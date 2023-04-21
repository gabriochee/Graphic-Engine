#pragma once
float degToRad(float deg);
float radToDeg(float rad);
float sign(SDL_Point p1, SDL_Point p2, SDL_Point p3);

bool inTriangle(Triangle* tri, SDL_Point* p);

SDL_Point RotatePoint(SDL_Point point, float angle);
SDL_Point RotatePoint(SDL_Point* point, float angle);
SDL_Point RotateFromPoint(SDL_Point* pivot, SDL_Point point, float angle);
SDL_Point PointToLocalSpace(SDL_Point* origin, SDL_Point* point);
SDL_Point PointToLocalSpace(SDL_Point* origin, SDL_Point* point, float angle);
SDL_Point PointToWorldSpace(SDL_Point* origin, SDL_Point* point);

void drawTriangle(Triangle* tri, SDL_Renderer* renderer);
void fillTriangle(Triangle* tri, SDL_Renderer* renderer);
void drawRectangle(Rectangle* rect, SDL_Renderer* renderer);
void fillRectangle(Rectangle* rect, SDL_Renderer* renderer);