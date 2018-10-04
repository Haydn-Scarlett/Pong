#include "Vector.h"


/**
*   @brief   Default Constructor.
*/
Vector::Vector()
{
	x = 0.0;
	y = 0.0;
}
/**
*   @brief   overloaded Constructor
*   @brief   sets the x and y values of the vector.
*/
Vector::Vector(float xval, float yval)
{
	x = xval;
	y = yval;
}

/**
*   @brief   Destructor.
*   @details Remove any non-managed memory and callbacks.
*/
Vector::~Vector()
{

}

/**
*   @brief   Get scalar 
*   @details Calculates the dot product of two vectors
*   @return  float
*/
float Vector::getScalar(Vector a)
{
	return((getVectorX() * a.getVectorX()) - (getVectorY() * a.getVectorY()));
}

/**
*   @brief   Get magnitude
*   @details Calculates the magnitude of the vector
*   @return  float
*/
float Vector::getMagnitude()
{
	return (sqrt(x * x) + (y * y));
}

/**
*   @brief   Set vector
*   @brief   sets the x and y values of the vector.
*   @return  void
*/
void Vector::setVector(float xval, float yval)
{
	x = xval;
	y = yval;
}

/**
*   @brief   Get vector X
*   @brief   gets the x values of the vector.
*   @return  float
*/
float Vector::getVectorX()
{
	return x;
}

/**
*   @brief   Get vector
*   @brief   gets the y value of the vector.
*   @return  float
*/
float Vector::getVectorY()
{
	return y;
}



/**
*   @brief   add
*   @details adds two vectors
*   @return  Vector
*/
Vector Vector::add(Vector a)
{
	Vector result(getVectorX() + a.getVectorX(), getVectorY() + a.getVectorY());
	return result;
}



/**
*   @brief   subtract
*   @details subtracts one vector from another
*   @return  Vector
*/
Vector Vector::subtract(Vector a)
{
	Vector result(getVectorX() - a.getVectorX(), getVectorY() + - a.getVectorY());
	return result;
}



/**
*   @brief   multiply
*   @details multiplys a vector by the scalar
*   @return  Vector
*/
Vector Vector::multiply(float scalar)
{
	Vector result(getVectorX() * scalar, getVectorY() * scalar);
	return result;
}

/**
*   @brief   normalise
*   @details normalises	a vector
*   @return  Vector
*/
Vector Vector::normalise()
{
	Vector result;
	float len = getMagnitude();
	if (len != 0.0f)
	{
		result.setVector(getVectorX() / len, getVectorY() / len);
	}
	else
	{
		result.setVector(0.0f, 0.0f);
	}

	return result;
}


/**
*   @brief   getDistance
*   @details gets the distance between two vectors
*   @return  float
*/
float Vector::getDistance(Vector a)
{
	return (float)sqrt((a.getVectorX() - getVectorX()) * 
		(a.getVectorX() - getVectorX()) + (a.getVectorY() - getVectorY()) *
		(a.getVectorY() - getVectorY()));
}