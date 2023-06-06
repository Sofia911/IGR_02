#ifndef VECTOR3F_H
#define VECTOR3F_H

#pragma once

class Vector3f
{
private:
	float x, y, z;

public:
	Vector3f() { x = 0; y = 0; z = 0; }
	Vector3f(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
	Vector3f operator+(Vector3f vec) const; // addition of two vectors
	Vector3f operator-(const Vector3f& vec); // subtraction of two vectors
	Vector3f operator*(Vector3f vec); // multiplication of two vectors
	float dot_product(Vector3f vec); // dot product of two vectors
	Vector3f cross_product(Vector3f vec); // cross product of two vectors
	Vector3f operator*(float scalar) const; // scalar multiplication
	Vector3f operator/(float scalar); // scalar division
	Vector3f operator-(float scalar); // subtraction of a scalar
	Vector3f uminus() const; // unary minus
	Vector3f normalize(); // normalize the vector
	float length(); // get the length of the vector
	Vector3f randPoint();
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	~Vector3f() {}
};
#endif



