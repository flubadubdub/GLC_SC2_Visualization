#ifndef ND_POINT_H
#define ND_POINT_H

#ifndef VECTOR_H
#include "Vector.h"
#endif

class ND_Point{
public:
	ND_Point(int, float*, Vector*, Point*);
	void draw(float, float, float);
	void drawGLC(float, float, float);
private:
	int numDimensions;
	float *ndPoint;
	Vector* repVectors;
	Point* repPoints;
};

#endif