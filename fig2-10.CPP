#include "Vector.h"
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>
#include <fstream>
#include "ND_Point.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 600;
float **nd_points;
std::string *classes;
Point* vertices;
Vector* vectors;
int numDimensions, numND_Pts, numTwoD_Pts;

void Display();
void Init(void);
void ReadData(std::string);
void ReadPoints(std::string);
void keyboardFunc(unsigned char key, int x, int y);

void main (int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Algorithm 5");
    glutDisplayFunc(Display);
    Init();
	glutKeyboardFunc(keyboardFunc);
	glutMainLoop();
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	std::string toRead = "iris_data.txt";
	ReadData(toRead);
	toRead = "glc_points3.txt";
	ReadPoints(toRead);
	float r = 1.0, g = 0.0, b = 0.0;
	std::string currentClass = classes[0];
	//std::cout << "numDimensions: " << numDimensions << std::endl << "numND_Pts: " << numND_Pts << std::endl << "numTwoD_Pts: " << numTwoD_Pts << std::endl << std::endl;
	//system("pause");
	for(int i = 0; i < numND_Pts; i++){
		std::string itrClass = classes[i];

		float *scalars = new float[numDimensions];
		Point *pts = new Point[numDimensions * 2];
		Vector *vcts = new Vector[numDimensions];

		if(!(itrClass == currentClass)){
			//change color to random new color
			r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			currentClass = itrClass;
		}
		//std::cout << "pts: ";
		for(int j = 0; j < numDimensions * 2; j++){
			pts[j] = vertices[(i * 8) + j];
			//std::cout << "(" << pts[j].getX() << ", " << pts[j].getY() << "), ";
		}
		//std::cout << std::endl << "---------------------------------------------\n";
		//system("pause");
		/*int j = 0;
		while(true){
			if(j == (numDimensions * 2)-2)
				break;
			std::cout << "(" << pts[j].getX() << ", " << pts[j].getY() << ")\n";
			std::cout << "(" << pts[j+1].getX() << ", " << pts[j+1].getY() << ")\n";
			vcts[j] = Vector(pts[j], pts[j+1]);
			std::cout << "j: " << j << std::endl;
			j=j+2;
		}*/
		int j = 0;
		for(int k = 0; k < numDimensions * 2 - 1; k++){

			vcts[j] = Vector(pts[k], pts[k+1]);
			++k;
			j++;
		}
		for(int j = 0; j < numDimensions; j++){
			scalars[j] = nd_points[i][j];
		}
		ND_Point ndp(numDimensions, scalars, vcts, pts);
		ndp.drawGLC(r, g, b);
	}
}

void Init()
{
	glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0f,0.0f,0.0f);
    glPointSize(4.0);
	glLineWidth(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(1.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT); //to show one point: 7.5, 11.0, 399.0, 430.0
																  //to show whole set: 0.0, SCREEN_WIDTH-72, 150.0, SCREEN_HEIGHT-150.0
}

void ReadData(std::string filename){
	std::ifstream inFile;
	std::string line;
	int numItems = 1, numLines = 0;
	int counter = 0;
	std::string readLine;
	inFile.open(filename);
	//for the first line, count the number of commas to find the number of items per line.
	if(inFile.good()){
		std::getline(inFile, readLine);
		for(int i = 0; i < readLine.length(); i++){
			if(readLine[i] == ','){
				numItems++;
			}
		}
		numDimensions = numItems - 1;
	}
	//std::cout << numItems<<std::endl;
	//return to beginning of file
	inFile.seekg(0, std::ios::beg);
	//read file to find number of lines in it
	while(std::getline(inFile, readLine)){
		++numLines;
	}
	numND_Pts = numLines;
	//std::cout<<numLines<<std::endl;
	//return to beginning of file
	inFile.clear();
	inFile.seekg(0, std::ios::beg);
	//initialize matrix and array to their appropriate sizes
	classes = new std::string[numLines];
	nd_points = new float*[numLines];
	for(int i = 0; i < numLines; i++){
		nd_points[i] = new float[numItems - 1];
	}
	//read file
	while(inFile.good()){
		int numStart = 0, numEnd;
		std::getline(inFile, readLine);
		int itemIndex = 0;
		for(int i = 0; i < readLine.length(); i++){
			if(readLine[i] == ','){
				std::string s = readLine.substr(numStart, i - numStart);
				nd_points[counter][itemIndex] = stof(s);
				//std::cout << readLine.substr(numStart, i - numStart) << std::endl;
				itemIndex++;
				numStart = i + 1;
				if(itemIndex == numItems - 1){
					classes[counter] = readLine.substr(numStart, readLine.length() - numStart);
					break;
				}
			}
		}
		counter++;
	}
	inFile.close();
	for(int i = 0; i < numLines; i++){
		for(int j = 0; j < numItems - 1; j++){
			//std::cout<< nd_points[i][j];
			//if(j != numItems-2)
				//std::cout<< ", ";
		}
		//std::cout<< std::endl;
	}
	
}

void ReadPoints(std::string fileName){
	std::ifstream inFile;
	std::string line;
	int numLines = 0;
	int readPt[2];
	inFile.open(fileName);
	//file being read is assumed to be list of 2-dimensional points
	//read file to find number of lines in it
	while(std::getline(inFile, line)){
		++numLines;
	}
	vertices = new Point[numLines];
	//return to beginning of file
	inFile.clear();
	inFile.seekg(0, std::ios::beg);
	int counter = 0;
	while(inFile.good()){
		std::getline(inFile, line);
		int numStart = 0, numEnd;
		for(int i = 0; i < line.length(); i++){
			if(line[i] == ','){
				numEnd = i;
				readPt[0] = stof(line.substr(numStart, numEnd - numStart));
				//std::cout << two_d_points[counter][0];
				numStart = i+1;
			}
			if(i == line.length() - 1){
				readPt[1] = stof(line.substr(numStart, line.length() - numStart));
				//std::cout << ", " << two_d_points[counter][1] << std::endl;
			}
			vertices[counter] = Point(readPt[0], readPt[1]);
		}
		counter++;
	}
	numTwoD_Pts = numLines;
	/*vectors = new Vector[counter/2];
	std::cout << "numVectors = " << counter/2 << std::endl;
	int i = -1;
	for(int j = 0; j < numTwoD_Pts/2; j++){
		//std::cout << "new vector with points (" << vertices[i+1].getX() << ", " << vertices[i+1].getY() << ") and (" << vertices[i+2].getX() << ", " << vertices[i+2].getY() << ")\n";
		vectors[j] = Vector(vertices[i+1], vertices[i+2]);
		i = i+2;
	}*/
}

void keyboardFunc(unsigned char key, int x, int y){
	float r = 1.0, g = 0.0, b = 0.0;
	std::string currentClass;
	std::string firstClass = classes[0];
	switch(key){
	case '1':
		glClear(GL_COLOR_BUFFER_BIT);
		for(int i = 0; i < numND_Pts; i++){
			std::string itrClass = classes[i];
			if(!(itrClass == currentClass)){
				break;
			}
			float *scalars = new float[numDimensions];
			Point *pts = new Point[numDimensions * 2];
			Vector *vcts = new Vector[numDimensions];
			
			for(int j = 0; j < numDimensions * 2; j++){
				pts[j] = vertices[(i * 8) + j];
			}
			int j = 0;
			for(int k = 0; k < numDimensions * 2 - 1; k++){
				vcts[j] = Vector(pts[k], pts[k+1]);
				++k;
				j++;
			}
			for(int j = 0; j < numDimensions; j++){
				scalars[j] = nd_points[i][j];
			}
			ND_Point ndp(numDimensions, scalars, vcts, pts);
			ndp.drawGLC(r, g, b);
		}
		break;
	case '2':
		r = 0.0, g = 1.0, b = 0.0;
		for(int i = 49; i < numND_Pts; i++){
			std::string itrClass = classes[i];
			while(itrClass == firstClass)
				continue;
			float *scalars = new float[numDimensions];
			Point *pts = new Point[numDimensions * 2];
			Vector *vcts = new Vector[numDimensions];
			if(!(itrClass == currentClass)){
				break;
			}
			for(int j = 0; j < numDimensions * 2; j++){
				pts[j] = vertices[(i * 8) + j];
			}
			int j = 0;
			for(int k = 0; k < numDimensions * 2 - 1; k++){
				vcts[j] = Vector(pts[k], pts[k+1]);
				++k;
				j++;
			}
			for(int j = 0; j < numDimensions; j++){
				scalars[j] = nd_points[i][j];
			}
			ND_Point ndp(numDimensions, scalars, vcts, pts);
			ndp.drawGLC(r, g, b);
		}
		break;
	case '3':
		r = 0.0, g = 1.0, b = 0.0;
		for(int i = 99; i < numND_Pts; i++){
			std::string itrClass = classes[i];
			while(itrClass == firstClass)
				continue;
			currentClass = itrClass;
			while(currentClass == itrClass)
				continue;
			float *scalars = new float[numDimensions];
			Point *pts = new Point[numDimensions * 2];
			Vector *vcts = new Vector[numDimensions];
			if(!(itrClass == currentClass)){
				break;
			}
			for(int j = 0; j < numDimensions * 2; j++){
				pts[j] = vertices[(i * 8) + j];
			}
			int j = 0;
			for(int k = 0; k < numDimensions * 2 - 1; k++){
				vcts[j] = Vector(pts[k], pts[k+1]);
				++k;
				j++;
			}
			for(int j = 0; j < numDimensions; j++){
				scalars[j] = nd_points[i][j];
			}
			ND_Point ndp(numDimensions, scalars, vcts, pts);
			ndp.drawGLC(r, g, b);
		}
		break;
	case '4':
		glClear(GL_COLOR_BUFFER_BIT);
		break;
	default:
		break;
	}
}