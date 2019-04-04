#ifndef POINT_H
#define POINT_H

#include <windows.h>
#include "glut.h"
#include <gl/GL.h>
#include <gl/Glu.h>

class Point{
public:
	Point();
	Point(float, float);
	Point(const Point&);
	float getX();
	float getY();
	void draw();
	void draw(float, float, float);
	Point copy();
private:
	float x, y;
};

#endif