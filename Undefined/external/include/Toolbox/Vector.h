#pragma once

#include <ostream>
#include <vector>

#include "flag.h"

class Vector2;
class Vector3;
class Vector4;

class Vector
{
public:

	TOOLBOX Vector();
	TOOLBOX Vector(size_t size, float initValue = 0.0f);
	TOOLBOX Vector(const std::initializer_list<float>& values);

	TOOLBOX ~Vector();

	TOOLBOX size_t size() const;
	
	TOOLBOX void setVectorValues(std::vector<float>& newValue);
	TOOLBOX float normVec() const;
	TOOLBOX float dotProduct(Vector& v) const;
	TOOLBOX float crossProductVec2(const Vector& v) const;
	TOOLBOX Vector crossProductVec3(Vector& v) const;
	TOOLBOX float angleVec2or3(Vector& v) const;
	TOOLBOX float dist(Vector& v) const;
	TOOLBOX Vector normalize() const;
	
	TOOLBOX Vector operator+(const Vector& v) const;
	TOOLBOX Vector operator*(float mult) const;
	TOOLBOX Vector operator/(float div) const;
	TOOLBOX Vector operator-(const Vector& v) const;
	TOOLBOX Vector operator-() const;

	TOOLBOX float& operator[](size_t index);
	TOOLBOX float operator[](size_t index) const;

	TOOLBOX explicit operator Vector2() const;
	TOOLBOX explicit operator Vector3() const;
	TOOLBOX explicit operator Vector4() const;


private:
	std::vector<float> mValues;
};

std::ostream& operator<<(std::ostream& out, Vector& v);
