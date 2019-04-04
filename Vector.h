#ifndef VECTOR_H
#define VECTOR_H

#ifndef POINT_H
#include "Point.h"
#endif

class Vector{
public:
	Vector();
	Vector(float, float);
	Vector(Point, Point);
	Vector(const Vector&);
	Vector operator+(const Vector&);
	float getX();
	float getY();
	float calcDistance(Point, Point);
	void draw(Point);
	void draw(Point, float, float, float, float);
	void draw(float, float, float, float);
	void applyScalar(float);
	Point getEndPoint(Point);
	Point getEndPoint(Point, float);
	Point getStartPoint(Point);
	Point getStartPoint(Point, float);
	void setDrawPoint(Point);
	float calcDistance(Point);
private:
	float x, y;
	Point drawPoint;
};

#endif