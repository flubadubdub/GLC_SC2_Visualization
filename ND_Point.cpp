#include "ND_Point.h"
#include <iostream>

ND_Point::ND_Point(int n, float* values, Vector* vectors, Point* points){
	this->numDimensions = n;
	this->ndPoint = values;
	this->repPoints = points;
	this->repVectors = vectors;
}

void ND_Point::draw(float r, float g, float b){
	for(int i = 0; i < this->numDimensions * 2; i++){
		//std::cout << "drawing point at (" << repPoints[i].getX() << ", " << repPoints[i].getY() << ")\n";
		repPoints[i].draw(r, g, b);
	}
	for(int i = 0; i < this->numDimensions; i++){
		repVectors[i].draw(ndPoint[i], r, g, b);
	}
}

void ND_Point::drawGLC(float r, float g, float b){
	repPoints[0].draw(r, g, b);
	Point pt, qt;				//pt - endpoint, qt - startpoint
	for(int i = 0; i < this->numDimensions; i++){
		if(i == 0){
			repVectors[i].draw(ndPoint[i]/8, r, g, b);						//draw first vector from its drawPoint
			pt = repVectors[i].getEndPoint(repPoints[i], ndPoint[i]/8);		//end point of first vector, therefore end point of second vector
			std::cout << "pt: (" << pt.getX() << ", " << pt.getY() << ")\n";
			i++;
			qt = repVectors[i].getStartPoint(pt, ndPoint[i]/8);				//start point of second vector
			repVectors[i].setDrawPoint(qt);
			repVectors[i].draw(qt, ndPoint[i]/8, r, g, b);					//draw second vector from qt
			pt = qt.copy();														//startpoint of second vector is endpoint for next
		}
		else{
			qt = repVectors[i].getStartPoint(pt, ndPoint[i]/8);
			repVectors[i].setDrawPoint(qt);
			repVectors[i].draw(qt, ndPoint[i]/8, r, g, b);
			pt = qt.copy();
		}
	}
}
