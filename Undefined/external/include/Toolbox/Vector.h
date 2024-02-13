#pragma once

#include <ostream>
#include <vector>

class Vector2;
class Vector3;
class Vector4;

class Vector
{
public:

	Vector();
	Vector(size_t size, float initValue = 0.0f);
	Vector(const std::initializer_list<float>& values);

	~Vector();

	size_t size() const;
	
	void setVectorValues(std::vector<float>& newValue);
	float normVec() const;
	float dotProduct(Vector& v) const;
	float crossProductVec2(const Vector& v) const;
	Vector crossProductVec3(Vector& v) const;
	float angleVec2or3(Vector& v) const;
	float dist(Vector& v) const;
	Vector normalize() const;
	
	Vector operator+(const Vector& v) const;
	Vector operator*(float mult) const;
	Vector operator/(float div) const;
	Vector operator-(const Vector& v) const;
	Vector operator-() const;

	float& operator[](size_t index);
	float operator[](size_t index) const;

	explicit operator Vector2() const;
	explicit operator Vector3() const;
	explicit operator Vector4() const;


private:
	std::vector<float> mValues;
};

std::ostream& operator<<(std::ostream& out, Vector& v);
