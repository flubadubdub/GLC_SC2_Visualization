#include "Vector.h"
#include <math.h>
#include <iostream>

# define M_PI 3.14159265358979323846  /* pi */
#define TWO_PI 6.28318530717958647692 /* 2pi */

Vector::Vector(){
	this->x = 0;
	this->y = 0;
}

Vector::Vector(float x, float y){
	this->x = x;
	this-> y = y;
}

Vector::Vector(Point start, Point end){
	this->x = end.getX() - start.getX();
	this->y = end.getY() - start.getY();
	//std::cout << "Vector: (" << this->x << ", " << this->y << ")\n";
	drawPoint = Point(start.getX(), start.getY());
	//std::cout << "drawPoint: (" << this->drawPoint.getX() << ", " << this->drawPoint.getY() << ")\n";
}

Vector::Vector(const Vector& other){
	this->x = other.x;
	this->y = other.y;
}

Vector Vector::operator+(const Vector& other){
	float xx = this->x + other.x;
	float yy = this->y + other.y;
	Vector v(xx, yy);
	return v;
}

float Vector::getX(){
	return this->x;
}

float Vector::getY(){
	return this->y;
}

void Vector::draw(Point p){
	glBegin(GL_LINES);
	glVertex2f(p.getX(), p.getY());
	glVertex2f(p.getX()+this->x, p.getY()+this->y);
	glEnd();
	glFlush();
}

void Vector::draw(Point p, float s, float r, float g, float b){
	glBegin(GL_LINES);
	//draw the line according to the scalar
	glColor4f(r, g, b, 1.0);
	glVertex2f(p.getX(), p.getY());
	float scaledX = p.getX() + (this->x * s);
	float scaledY = p.getY() + (this->y * s);
	Point scaled(scaledX, scaledY);
	glVertex2f(scaledX, scaledY);
	glEnd();
	//std::cout << "scalar: " << s << std::endl;
	//std::cout << "scaled point-vector: (" << scaledX << ", " << scaledY << ")\n";
	//draw the arrow head
	//find the length of the scaled vector we just drew
	float radius = calcDistance(scaled, p);
	//std::cout << "radius: " << radius << std::endl;
	//the first point exists radius pixels away from the initial point, straight up
	Point triPtA(p.getX(), p.getY()+radius);
	//std::cout << "triPtA: (" << triPtA.getX() << ", " << triPtA.getY() << ")\n";
	//the second and third points make an equilateral triangle
	Point triPtB(p.getX()-5, p.getY()+radius-5);
	//std::cout << "triPtB: (" << triPtB.getX() << ", " << triPtB.getY() << ")\n";
	Point triPtC(p.getX()+5, p.getY()+radius-5);
	//std::cout << "triPtC: (" << triPtC.getX() << ", " << triPtC.getY() << ")\n";
	//find the distance between triPtA and the end of the vector
	float dist = calcDistance(scaled, triPtA);
	//std::cout << "dist: " << dist << std::endl;
	//calculate radius for triPtB and triPtC
	float arrowRadius = calcDistance(triPtB, p);
	//std::cout << "arrowRadius: " << arrowRadius << std::endl;
	//find the angle between the two points on the circumference
	float theta = (acos(((2*radius*radius)-(dist*dist))/(2*radius*radius)));
	if(this->x > 0)
		theta = 2*M_PI - theta;
	else{
		theta = fmod(theta, TWO_PI);
	}
	//std::cout<<"theta: " << theta << std::endl;

	//rotate triPtB and triPtC
	float sn = sin(theta);
	float cs = cos(theta);
	float pivotBX = triPtB.getX() - p.getX();
	//std::cout << "pivotBX = " <<triPtB.getX() << " - " << p.getX() << std::endl;
	float pivotBY = triPtB.getY() - p.getY();
	//std::cout << "pivotBY = " <<triPtB.getY() << " - " << p.getY() << std::endl;
	float finalBx = pivotBX * cs - pivotBY * sn;
	//std::cout << "finalBx = " << pivotBX << " * " << cs << " - " << pivotBY << " * " << sn <<  " = " << finalBx << std::endl;
	finalBx += p.getX();
	float finalBy = triPtB.getY() - p.getY();
	finalBy = pivotBX * sn + pivotBY * cs;
	finalBy += p.getY();
	//std::cout<<"finalB: ("<<finalBx << ", " << finalBy << ")\n";
	Point finalB(finalBx, finalBy);

	float pivotCX = triPtC.getX() - p.getX();
	//std::cout << "pivotCX = " <<triPtC.getX() << " - " << p.getX() << std::endl;
	float pivotCY = triPtC.getY() - p.getY();
	//std::cout << "pivotCY = " <<triPtC.getY() << " - " << p.getY() << std::endl;
	float finalCx = pivotCX * cs - pivotBY * sn;
	//std::cout << "finalCX = " <<pivotCX << " * " << cs << " - " << pivotCY << " * " << sn << std::endl;
	finalCx += p.getX();
	float finalCy = triPtC.getY() - p.getY();
	finalCy = pivotCX * sn + pivotCY * cs;
	finalCy += p.getY();
	//std::cout<<"finalC: ("<<finalCx << ", " << finalCy << ")\n";
	Point finalC(finalCx, finalCy);
	//draw the triangle with the rotated points
	glBegin(GL_TRIANGLES);
	glVertex2f(scaled.getX(), scaled.getY());
	glVertex2f(finalB.getX(), finalB.getY());
	glVertex2f(finalC.getX(), finalC.getY());
	glEnd();
	glFlush();
	//reset drawing color
	glColor3f(0.0, 0.0, 0.0);
}

void Vector::applyScalar(float s){
	this->x *= s;
	this->y *= s;
}

void Vector::draw(float s, float r, float g, float b){
	glBegin(GL_LINES);
	//draw the line according to the scalar
	glColor4f(r, g, b, 1.0);
	glVertex2f(this->drawPoint.getX(), this->drawPoint.getY());
	float scaledX = this->drawPoint.getX() + (this->x * s);
	float scaledY = this->drawPoint.getY() + (this->y * s);
	Point scaled(scaledX, scaledY);
	glVertex2f(scaledX, scaledY);
	glEnd();
	//std::cout << "scalar: " << s << std::endl;
	//std::cout << "scaled point-vector: (" << scaledX << ", " << scaledY << ")\n";
	//draw the arrow head
	//find the length of the scaled vector we just drew
	float radius = calcDistance(scaled);
	//std::cout << "radius: " << radius << std::endl;
	//the first point exists radius pixels away from the initial point, straight up
	Point triPtA(this->drawPoint.getX(), this->drawPoint.getY()+radius);
	//std::cout << "triPtA: (" << triPtA.getX() << ", " << triPtA.getY() << ")\n";
	//the second and third points make an equilateral triangle
	Point triPtB(this->drawPoint.getX()-5, this->drawPoint.getY()+radius-5);
	//std::cout << "triPtB: (" << triPtB.getX() << ", " << triPtB.getY() << ")\n";
	Point triPtC(this->drawPoint.getX()+5, this->drawPoint.getY()+radius-5);
	//std::cout << "triPtC: (" << triPtC.getX() << ", " << triPtC.getY() << ")\n";
	//find the distance between triPtA and the end of the vector
	float dist = calcDistance(scaled, triPtA);
	//std::cout << "dist: " << dist << std::endl;
	//calculate radius for triPtB and triPtC
	float arrowRadius = calcDistance(triPtB);
	//std::cout << "arrowRadius: " << arrowRadius << std::endl;
	//find the angle between the two points on the circumference
	float theta = (acos(((2*radius*radius)-(dist*dist))/(2*radius*radius)));
	if(this->x > 0)
		theta = 2*M_PI - theta;
	else{
		theta = fmod(theta, TWO_PI);
	}
	//std::cout<<"theta: " << theta << std::endl;

	//rotate triPtB and triPtC
	float sn = sin(theta);
	float cs = cos(theta);
	float pivotBX = triPtB.getX() - this->drawPoint.getX();
	//std::cout << "pivotBX = " <<triPtB.getX() << " - " << this->drawPoint.getX() << std::endl;
	float pivotBY = triPtB.getY() - this->drawPoint.getY();
	//std::cout << "pivotBY = " <<triPtB.getY() << " - " << this->drawPoint.getY() << std::endl;
	float finalBx = pivotBX * cs - pivotBY * sn;
	//std::cout << "finalBx = " << pivotBX << " * " << cs << " - " << pivotBY << " * " << sn <<  " = " << finalBx << std::endl;
	finalBx += this->drawPoint.getX();
	float finalBy = triPtB.getY() - this->drawPoint.getY();
	finalBy = pivotBX * sn + pivotBY * cs;
	finalBy += drawPoint.getY();
	//std::cout<<"finalB: ("<<finalBx << ", " << finalBy << ")\n";
	Point finalB(finalBx, finalBy);

	float pivotCX = triPtC.getX() - this->drawPoint.getX();
	//std::cout << "pivotCX = " <<triPtC.getX() << " - " << this->drawPoint.getX() << std::endl;
	float pivotCY = triPtC.getY() - this->drawPoint.getY();
	//std::cout << "pivotCY = " <<triPtC.getY() << " - " << this->drawPoint.getY() << std::endl;
	float finalCx = pivotCX * cs - pivotBY * sn;
	//std::cout << "finalCX = " <<pivotCX << " * " << cs << " - " << pivotCY << " * " << sn << std::endl;
	finalCx += this->drawPoint.getX();
	float finalCy = triPtC.getY() - this->drawPoint.getY();
	finalCy = pivotCX * sn + pivotCY * cs;
	finalCy += this->drawPoint.getY();
	//std::cout<<"finalC: ("<<finalCx << ", " << finalCy << ")\n";
	Point finalC(finalCx, finalCy);
	//draw the triangle with the rotated points
	glBegin(GL_TRIANGLES);
	glVertex2f(scaled.getX(), scaled.getY());
	glVertex2f(finalB.getX(), finalB.getY());
	glVertex2f(finalC.getX(), finalC.getY());
	glEnd();
	glFlush();
	//reset drawing color
	glColor3f(0.0, 0.0, 0.0);
	//std::cout << "---------------------------------------------------------\n";
}

float Vector::calcDistance(Point p1, Point p2){
	float d = sqrtf(((abs(p1.getX() - p2.getX()))*(abs(p1.getX()-p2.getX())))+((abs(p1.getY()-p2.getY()))*(abs(p1.getY()-p2.getY()))));
	//std::cout << "d: " << d << std::endl;
	return d;
}

float Vector::calcDistance(Point p){
	float d = sqrtf(((abs(p.getX() - this->drawPoint.getX()))*(abs(p.getX()-this->drawPoint.getX())))+((abs(p.getY()-this->drawPoint.getY()))*(abs(p.getY()-this->drawPoint.getY()))));
	//std::cout << "1-arg d: " << d << std::endl;
	return d;
}

void Vector::setDrawPoint(Point p){
	this->drawPoint = Point(p.getX(), p.getY());
}

Point Vector::getEndPoint(Point p){
	Point q(p.getX()+this->x, p.getY()+this->y);
	return q;
}

Point Vector::getEndPoint(Point p, float s){
	Point q(p.getX()+this->x*s, p.getY()+this->y*s);
	return q;
}

Point Vector::getStartPoint(Point p){
	Point q(p.getX()-this->x, p.getY()-this->y);
	return q;
}

Point Vector::getStartPoint(Point p, float s){
	Point q(p.getX()-(this->x*s), p.getY()-(this->y*s));
	return q;
}