#include "Point.h"
#include <iostream>

//default constructor
Point::Point(){
	this->x = 0;
	this->y = 0;
}

//constructor creates point using 2 float arguments
Point::Point(float x, float y){
	this->x = x;
	this->y = y;
	//std::cout << "Point: (" << this->x << ", " << this->y << ")\n";
}

//copy constructor
Point::Point(const Point& other){
	this->x = other.x;
	this->y = other.y;
}

//returns point's private x value
float Point::getX(){
	return this->x;
}

//returns point's private y value
float Point::getY(){
	return this->y;
}

//draws point using its x and y values
void Point::draw(){
	glBegin(GL_POINTS);
	glVertex2f(this->x, this->y);
	glEnd();
	glFlush();
}

void Point::draw(float r, float g, float b){
	glBegin(GL_POINTS);
	glColor3f(r, g, b);
	glVertex2f(this->x, this->y);
	glEnd();
	glFlush();
	//reset drawing color
	glColor3f(0.0, 0.0, 0.0);
}

Point Point::copy(){
	Point p(this->x, this->y);
	return p;
}