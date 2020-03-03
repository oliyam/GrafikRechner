#pragma once

/*
header file providing vector objects and some useful functions
made by me (Jan Oliver Yameogo) ... lol
*/

#include <string>
#include <iostream>
#include <cmath>

using std::string;
using namespace std;

//class for 2 dimensional vector
class vec2
{
private:
	double x, y;

public:
	//constructors
	vec2()
	{
		x = 0;
		y = 0;
	}
	vec2(double x, double y)
	{
		this->x = x;
		this->y = y;
	}

	//getters
	double getX() { return x; }
	double getY() { return y; }

	//setters
	void setX(double x) { this->x = x; }
	void setY(double y) { this->y = y; }

	string toString()
	{
		return "x: " + to_string(x) + "; y: " + to_string(y);
	}

	//operators for vec2 objects

	//vector plus vector
	vec2 operator+ (vec2 vec)
	{
		return vec2(x + vec.getX(), y + vec.getY());
	}
	//vector minus vector
	vec2 operator- (vec2 vec)
	{
		return vec2(x - vec.getX(), y - vec.getY());
	}
	//vector multiplly operator
	vec2 operator* (vec2 vec)
	{
		return(vec2(x * vec.getX(), y * vec.getY()));
	}
	//vector multiplly operator
	vec2 operator* (double vec)
	{
		return(vec2(x * vec, y * vec));
	}
	//vector division operator
	vec2 operator/ (double vec)
	{
		return(vec2(x / vec, y / vec));
	}
	//stream operator overload as a to string
	friend ostream& operator<< (ostream& stream, vec2 vec)
	{
		return stream << vec.toString();
	}
};

//class for 3 dimensional vector
class vec3
{
private:
	double x, y, z;

public:
	//constructors
	vec3()
	{
		x = 0;
		y = 0;
		z = 0;
	}
	vec3(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	//getters
	double getX() { return x; }
	double getY() { return y; }
	double getZ() { return z; }

	//setters
	void setX(double x) { this->x = x; }
	void setY(double y) { this->y = y; }
	void setZ(double z) { this->z = z; }

	string toString()
	{
		return "x: " + to_string(x) + "; y: " + to_string(y) + "; z: " + to_string(z);
	}

	//operators for vec3 objects 

	//stream operator overload as a to string
	friend ostream& operator<< (ostream& stream, vec3 vec)
	{
		return stream << vec.toString();
	}

	//vector plus vector
	vec3 operator+ (vec3 vec)
	{
		return vec3(x + vec.getX(), y + vec.getY(), z + vec.getZ());
	}
	//vector minus vector
	vec3 operator- (vec3 vec)
	{
		return vec3(x - vec.getX(), y - vec.getY(), z - vec.getZ());
	}
	//dotproduct
	double operator* (vec3 vec)
	{
		return x * vec.getX() + y * vec.getY() + z * vec.getZ();
	}
	//crossproduct
	vec3 operator% (vec3 vec)
	{
		return vec3(
			(y * vec.getZ()) - (z * vec.getY()),
			(z * vec.getX()) - (x * vec.getZ()),
			(x * vec.getY()) - (y * vec.getX())
		);
	}
	//product with a scalar
	vec3 operator *(double d)
	{
		return vec3(x * d, y * d, z * d);
	}
	//quotient with a scalar
	vec3 operator /(double d)
	{
		return vec3(x / d, y / d, z / d);
	}

	//= vector assignment operators

	//vector plus vector
	void operator+= (vec3 vec)
	{
		x += vec.getX();
		y += vec.getY();
		z += vec.getZ();
	}
	//vector minus vector
	void operator-= (vec3 vec)
	{
		x -= vec.getX();
		y -= vec.getY();
		z -= vec.getZ();
	}
	//crossproduct
	void operator%= (vec3 vec)
	{
		x = (y * vec.getZ()) - (z * vec.getY());
		y = (z * vec.getX()) - (x * vec.getZ());
		z = (x * vec.getY()) - (y * vec.getX());
	}
	//product with a scalar
	void operator*= (double d)
	{
		x *= d;
		y *= d;
		z *= d;
	}
	//quotient with a scalar
	void operator/=(double d)
	{
		x /= d;
		y /= d;
		z /= d;
	}
	/*
	useful functions for vectors
	*/

	//returns the length of this vector
	double length()
	{
		return sqrt(x * x + y * y + z * z);
	}

	//returns the unit vector (vector of the same direction but woth the lenght of 1)
	vec3 unit()
	{
		return *this / length();
	}

	//distance between two three dimensional vectors in space
	double distance(vec3 vec)
	{
		return (*this - vec).length();
	}

	//(smallest) angle between 2 vectors in space
	double angle(vec3 vec)
	{
		float l = 1;
		if (isnan(acos((*this * vec) / (length() * vec.length())))) {
			if (-1 == (int)((*this * vec) / (length() * vec.length())))
				return 180;
			else
				return 0;
		}
		return acos((*this * vec) / (length() * vec.length())) * 180 / 3.14159;
	}

	//returns this point rotated around the vector vec by the angle of angle
	vec3 rotate(vec3 vec, double angle)
	{
		vec = vec.unit();

		double
			ux = vec.getX(), uy = vec.getY(), uz = vec.getZ(),
			c = cos(angle * 3.14159 / 180), s = sin(angle * 3.14159 / 180),


			xr = (x * (c + ux * ux * (1 - c)) + y * (ux * uy * (1 - c) - uz * s) + z * (ux * uz * (1 - c) + uy * s)),
			yr = (x * (ux * uy * (1 - c) + uz * s) + y * (c + uy * uy * (1 - c)) + z * (uz * uy * (1 - c) - ux * s)),
			zr = (x * (ux * uz * (1 - c) - uy * s) + y * (uz * uy * (1 - c) + ux * s) + z * (c + uz * uz * (1 - c)));

		return vec3(xr, yr, zr);
	}
};