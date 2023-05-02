#pragma once
float degToRad(float deg);
float radToDeg(float rad);
float sign(SDL_Point p1, SDL_Point p2, SDL_Point p3);
float sign(SDL_Point p1, SDL_Vertex* v1, SDL_Vertex* v2);

bool inTriangle(Triangle* tri, SDL_Point* p);

SDL_Point RotatePoint(SDL_Point point, float angle);
SDL_Point RotatePoint(SDL_Point* point, float angle);
SDL_Point PointToLocalSpace(SDL_Point* origin, SDL_Point* point);
SDL_Point PointToLocalSpace(SDL_Point* origin, SDL_Point* point, float angle);
SDL_Point PointToWorldSpace(SDL_Point* origin, SDL_Point* point);

SDL_Vertex RotatePoint(SDL_Vertex* vertex, float angle);
SDL_Vertex PointToLocalSpace(SDL_Point* origin, SDL_Vertex* vertex);
SDL_Vertex PointToLocalSpace(SDL_Point* origin, SDL_Vertex* vertex, float angle);
SDL_Vertex PointToWorldSpace(SDL_Point* origin, SDL_Vertex vertex);

void drawTriangle(Triangle* tri, SDL_Renderer* renderer);
void drawRectangle(Rectangle* rect, SDL_Renderer* renderer);
void drawCircle(Circle* circ, SDL_Renderer* renderer, int precision);
void drawShape(Shape* shape, SDL_Renderer* renderer);
void setTriangleColor(Triangle* t, SDL_Color c);
void setShapeColor(Shape* s, SDL_Color c);

Triangle* getRectangleRepresentation(Rectangle* rect);
std::vector<Triangle> getCircleRepresentation(Circle* circ, int precision);
