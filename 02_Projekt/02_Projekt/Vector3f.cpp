#include "Vector3f.h"
#include <iostream>

using namespace std;

Vector3f Vector3f::operator+(Vector3f vec) const
{
	return Vector3f(x + vec.x, y + vec.y, z + vec.z);
}

Vector3f Vector3f::operator-(const Vector3f& vec)
{
	return Vector3f(x - vec.x, y - vec.y, z - vec.z);
}

Vector3f Vector3f::operator*(Vector3f vec)
{
	return Vector3f(x * vec.x, y * vec.y, z * vec.z);
}

float Vector3f::dot_product(Vector3f vec)
{
	return x * vec.x + vec.y * y + vec.z * z;
}

Vector3f Vector3f::cross_product(Vector3f vec)
{
	float ni = y * vec.z - z * vec.y;
	float nj = z * vec.x - x * vec.z;
	float nk = x * vec.y - y * vec.x;
	return Vector3f(ni, nj, nk);
}

Vector3f Vector3f::operator*(float scalar) const
{
	return Vector3f(x * scalar, y * scalar, z * scalar);
}


Vector3f Vector3f::operator/(float scalar)
{
	if (scalar == 0) {
		std::cout << "Error: Division by zero!" << std::endl;
		return Vector3f(x, y, z);
	}
	else {
		return Vector3f(x / scalar, y / scalar, z / scalar);
	}

}

Vector3f Vector3f::operator-(float scalar)
{
	return Vector3f(x - scalar, y - scalar, z - scalar);
}

Vector3f Vector3f::uminus() const
{
	return Vector3f(-x, -y, -z);
}

Vector3f Vector3f::normalize()
{
	float length = sqrt(x * x + y * y + z * z);
	return Vector3f(x / length, y / length, z / length);
}

float Vector3f::length()
{
	return float(sqrt(x * x + y * y + z * z));
}

Vector3f Vector3f::randPoint()
{
	float x_rand = -10.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (10.0f + 10.0f)));
	float y_rand = 10.6f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (12.0f - 10.6f)));
	float z_rand = -3.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.0f + 3.0f)));
	
	// generate points over the edges of the plane
	//float x_rand = -11.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (11.0f + 11.0f)));
	//float y_rand = 10.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (12.0f - 10.0f)));
	//float z_rand = -4.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.0f + 4.0f)));
	
	return Vector3f(x_rand, y_rand, z_rand);
}

