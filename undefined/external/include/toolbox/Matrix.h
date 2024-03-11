#pragma once

#include <vector>
#include <ostream>
#include <vector>

#include "flag.h"

class Vector;
class Matrix2x2;
class Matrix3x3;
class Matrix4x4;

class Matrix
{
public:
	TOOLBOX Matrix();
	TOOLBOX Matrix(size_t nbrOfRow, size_t nbrOfColumn, float initValue = 0.0f);
	TOOLBOX Matrix(const std::initializer_list<Vector>& values);

	TOOLBOX ~Matrix();

	TOOLBOX bool IsDiagonal();
	TOOLBOX static Matrix Identity(const size_t size);
	TOOLBOX float Trace() const;
	TOOLBOX Matrix Transpose() const;
	TOOLBOX Matrix SubMatrix(size_t rowIndex, size_t columnIndex, size_t rowNbr, size_t columnNbr) const;
	TOOLBOX float Det() const;
	TOOLBOX Matrix GaussJordan() const;
	TOOLBOX Matrix Augment(const Matrix& m) const;
	TOOLBOX Matrix Inverse() const;
	TOOLBOX static Matrix Set2DRotation(float angle);
	TOOLBOX static Matrix Set3DRotation(const float angle, Vector axis);
	TOOLBOX static Matrix Set3DRotation(const float cos, const float sin, Vector& axis);
	TOOLBOX static Matrix Set2DScaling(float alpha, float beta);
	TOOLBOX static Matrix Set3DScaling(float alpha, float beta, float gamma);
	TOOLBOX static Matrix SetTRS(float angle, Vector& axis, Vector& translate, Vector& scalingCoef);
	TOOLBOX size_t getRowNbr() const;
	TOOLBOX void copy(Matrix& dst) const;

	TOOLBOX Matrix operator+(Matrix& m) const;
	TOOLBOX Matrix operator-(Matrix& m) const;
	TOOLBOX Matrix operator*(float mult) const;
	TOOLBOX Matrix operator*(Matrix& m) const;
	TOOLBOX Vector operator*(const Vector& v) const;
	TOOLBOX Matrix operator-() const;

	TOOLBOX explicit operator Matrix2x2();
	TOOLBOX explicit operator Matrix3x3();
	TOOLBOX explicit operator Matrix4x4();

	TOOLBOX Vector& operator[](size_t index);
	TOOLBOX Vector operator[](size_t index) const;

private:
	std::vector<Vector> mValues;
	size_t nbrOfRow = 0, nbrOfColumn = 0;
	bool square = false;
	bool diagonal = false;
};

std::ostream& operator<<(std::ostream& out, Matrix& m);