#pragma once
#include <string>
#include "Constants.h"


class Vector
{
public:
	Vector();
	Vector(float xval, float yval);
	~Vector();


	// function to calculate dot product of a vector
	float getScalar(Vector a);
	// function to add two vectors
	Vector add(Vector a);
	// function to subtract two vectors
	Vector subtract(Vector a);
	// function to multiply a vector
	Vector multiply(float scalar);
	// function to calculate distance between two vectors
	float getDistance(Vector a);
	// function to normalize a vector (unit vector)
	Vector normalise();
	// function to calculate magnitude of a vector
	float getMagnitude();
	// function to set a vectors x and y values
	void setVector(float xval, float yval);
	// function to get a vectors x value
	float getVectorX();
	// function to set a vectors y value
	float getVectorY();


private:
	// position on the x axis
	float x = 0.0;
	// position on the y axis
	float y = 0.0;
};


