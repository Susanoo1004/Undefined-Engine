#pragma once

#include <ostream>
#include <vector>

#include "flag.h"

class Matrix;
class Vector;
class Vector3;
class Vector2;

/// @brief The Vector4 class represents either a four-dimensional vector or a point.
class TOOLBOX Vector4
{
public:
	float x, y, z, w;

	static Vector4 UnitX() { return Vector4(1.0f, 0.0f, 0.0f, 0.0f); }
	static Vector4 UnitY() { return Vector4(0.0f, 1.0f, 0.0f, 0.0f); }
	static Vector4 UnitZ() { return Vector4(0.0f, 0.0f, 1.0f, 0.0f); }
	static Vector4 UnitW() { return Vector4(0.0f, 0.0f, 0.0f, 1.0f); }

	Vector4();
	/// @brief Constructs a Vector4 with all its components set to 'xyzw'.
	Vector4(const float xyzw);
	Vector4(const float x, const float y, const float z, const float w);
	Vector4(const std::initializer_list<float>& values);
	/// @brief Constructs a Vector4 from point 'p1' to point 'p2'
	Vector4(const Vector4& p1, const Vector4& p2);

	/// @brief Returns the length of the vector.
	[[nodiscard]]
	float Norm() const;
	/// @brief Returns the squared length of the vector.
	[[nodiscard]]
	float SquaredNorm() const;

	/// @brief Normalizes the vector.
	/// @return A vector with the same direction but a length of one.
	[[nodiscard]]
	Vector4 Normalized() const;
	/// @brief Returns the dot product of this Vector4& with 'other'.
	[[nodiscard]]
	float Dot(const Vector4& other) const;

	/// @brief Returns a · b.
	[[nodiscard]]
	static float Dot(const Vector4& a, const Vector4& b);

	[[nodiscard]]
	float  operator[](const size_t i) const;
	[[nodiscard]]
	float& operator[](const size_t i);

    operator Matrix() const;
	operator Vector();
	explicit operator Vector3();
	explicit operator Vector2();

    // Automatically generates all comparison operators
	[[nodiscard]]
	friend auto operator<=>(const Vector4& a, const Vector4& b) = default;
};

[[nodiscard]]
Vector4 operator+(const Vector4& a, const Vector4& b);
[[nodiscard]]
Vector4 operator-(const Vector4& a, const Vector4& b);
[[nodiscard]]
Vector4 operator-(const Vector4& a);
[[nodiscard]]
Vector4 operator*(const Vector4& a, const Vector4& b);
[[nodiscard]]
Vector4 operator*(const Vector4& v, const float factor);
[[nodiscard]]
Vector4 operator/(const Vector4& a, const Vector4& b);
[[nodiscard]]
Vector4 operator/(const Vector4& v, const float factor);

Vector4& operator+=(Vector4& a, const Vector4& b);
Vector4& operator+=(Vector4& v, const float factor);
Vector4& operator-=(Vector4& a, const Vector4& b);
Vector4& operator-=(Vector4& v, const float factor);
Vector4& operator*=(Vector4& a, const Vector4& b);
Vector4& operator*=(Vector4& v, const float factor);
Vector4& operator/=(Vector4& a, const Vector4& b);
Vector4& operator/=(Vector4& v, const float factor);

bool operator==(const Vector4& v, const float f);
bool operator!=(const Vector4& v, const float f);
bool operator<(const Vector4& v, const float f);
bool operator>(const Vector4& v, const float f);
bool operator<=(const Vector4& v, const float f);
bool operator>=(const Vector4& v, const float f);

std::ostream& operator<<(std::ostream& out, const Vector4& v);
