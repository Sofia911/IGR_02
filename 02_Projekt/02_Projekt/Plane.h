#ifndef PLANE_H
#define PLANE_H
#pragma once

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Vector3f.h"
#include<cmath>



class Plane
{
private:
	Vector3f A, B, C, D;
	Vector3f normal;
public:
	Plane(Vector3f A_, Vector3f B_, Vector3f C_, Vector3f D_) { this->A = A_;  this->B = B_; this->C = C_; this->D = D_; }
	bool hit(Vector3f pos);
	void draw();
	Vector3f getA() { return A; }
	Vector3f getB() { return B; }
	Vector3f getC() { return C; }
	Vector3f getD() { return D; }
	Vector3f getNormal() { return normal; }
	~Plane(){}
};




#endif // !PLANE_H