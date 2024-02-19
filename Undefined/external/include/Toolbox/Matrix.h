#pragma once

#include <vector>
#include <ostream>
#include <vector>

class Vector;
class Matrix2x2;
class Matrix3x3;
class Matrix4x4;

class Matrix
{
public:
	Matrix();
	Matrix(size_t nbrOfRow, size_t nbrOfColumn, float initValue = 0.0f);
	Matrix(const std::initializer_list<Vector>& values);

	~Matrix();

	bool IsDiagonal();
	static Matrix Identity(const size_t size);
	float Trace() const;
	Matrix Transpose() const;
	Matrix SubMatrix(size_t rowIndex, size_t columnIndex, size_t rowNbr, size_t columnNbr) const;
	float Det() const;
	Matrix GaussJordan() const;
	Matrix Augment(const Matrix& m) const;
	Matrix Inverse() const;
	static Matrix Set2DRotation(float angle);
	static Matrix Set3DRotation(const float angle, Vector axis);
	static Matrix Set3DRotation(const float cos, const float sin, Vector& axis);
	static Matrix Set2DScaling(float alpha, float beta);
	static Matrix Set3DScaling(float alpha, float beta, float gamma);
	static Matrix SetTRS(float angle, Vector& axis, Vector& translate, Vector& scalingCoef);
	size_t getRowNbr() const;
	void copy(Matrix& dst) const;

	Matrix operator+(Matrix& m) const;
	Matrix operator-(Matrix& m) const;
	Matrix operator*(float mult) const;
	Matrix operator*(Matrix& m) const;
	Vector operator*(const Vector& v) const;
	Matrix operator-() const;

	explicit operator Matrix2x2();
	explicit operator Matrix3x3();
	explicit operator Matrix4x4();

	Vector& operator[](size_t index);
	Vector operator[](size_t index) const;

private:
	std::vector<Vector> mValues;
	size_t nbrOfRow = 0, nbrOfColumn = 0;
	bool square = false;
	bool diagonal = false;
};

std::ostream& operator<<(std::ostream& out, Matrix& m);