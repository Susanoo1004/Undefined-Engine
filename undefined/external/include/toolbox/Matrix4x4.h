#pragma once

#include <compare>
#include <ostream>
#include <vector>

#include "Vector4.h"
#include "flag.h"

class Matrix;
class Matrix2x2;
class Matrix3x3;
class Vector;
class Vector3;
class Quaternion;

/// @brief The Matrix4x4 class represents a two-dimensional array mainly used for mathematical operations.
class TOOLBOX Matrix4x4
{
public:
    /// @brief Returns the identity matrix.
    ///        The identity matrix is a matrix with its diagonal
    ///        set to one and everything else set to zero.
    static Matrix4x4 Identity();

    /// @brief Creates a matrix with all its values set to this default value.
    Matrix4x4(const float defaultValue = 0.f);
    Matrix4x4(const Vector4& r0, const Vector4& r1, const Vector4& r2, const Vector4& r3);
    Matrix4x4(
        const float r00, const float r01, const float r02, const float r03,
        const float r10, const float r11, const float r12, const float r13,
        const float r20, const float r21, const float r22, const float r23,
        const float r30, const float r31, const float r32, const float r33
    );
    /// @brief Copies the content of the given matrix to this one.
    Matrix4x4(const Matrix4x4& matrix);

    /// @brief Returns whether the matrix has everything except its diagonal set to zero.
    [[nodiscard]]
    bool IsDiagonal() const;
    /// @brief Returns whether the matrix is the identity matrix.
    ///        If this returns true, Matrix4x4::Identity() == *this should be true.
    [[nodiscard]]
    bool IsIdentity() const;
    /// @brief Returns wether this matrix has everything set to zero.
    [[nodiscard]]
    bool IsNull() const;
    /// @brief Returns whether the matrix is symmetric by its diagonal elements.
    [[nodiscard]]
    bool IsSymmetric() const;
    /// @brief Returns whether the matrix is symmetric by its diagonal elements
    ///        but one of the sides is the opposite of the other.
    [[nodiscard]]
    bool IsAntisymmetric() const;
    /// @brief Returns the diagonal elements of the matrix.
    [[nodiscard]]
    Vector4 Diagonal() const;
    /// @brief Returns the sum of the diagonal elements of the matrix.
    [[nodiscard]]
    float Trace() const;
    /// @brief Returns a matrix with its data set to the given indices of this one.
    [[nodiscard]]
    Matrix4x4 SubMatrix(const size_t rowIndex, const size_t colIndex, const size_t rows, const size_t cols) const;
    /// @brief Returns the determinant of this matrix.
    [[nodiscard]]
    float Determinant() const;
    /// @brief Sets this matrix to the identity matrix.
    Matrix4x4& LoadIdentity();
    /// @brief Switches the matrix by its diagonal elements.
    Matrix4x4& Transpose();
    Matrix4x4& Inverse();

    /// @brief Switches the given matrix by its diagonal elements.
    [[nodiscard]]
    static Matrix4x4 Transpose(const Matrix4x4& matrix);
    /// @brief Adds the 'm2' to the right of 'm1'.
    /// @brief Computes the inverse of the given matrix using the Gauss-Jordan pivot.
    [[nodiscard]]
    static Matrix4x4 Inverse(const Matrix4x4& matrix);
    /// @brief Creates a 3D translation matrix from the given angle for each of the x, y, and z axis.
    [[nodiscard]]
    static Matrix4x4 TranslationMatrix3D(const Vector3& translation);
    /// @brief Creates a 3D rotation matrix from the given angle and axis.
    /// @param angle The angle in radians.
    [[nodiscard]]
    static Matrix4x4 RotationMatrix3D(const float angle, const Vector3& axis);
    /// @brief Creates a 3D rotation matrix around the X axis from the given angle.
    /// @param angle The angle in radians.
    [[nodiscard]]
    static Matrix4x4 RotationMatrix3DX(const float angle);
    /// @brief Creates a 3D rotation matrix around the X axis from the given angle.
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    [[nodiscard]]
    static Matrix4x4 RotationMatrix3DX(const float cos, const float sin);
    /// @brief Creates a 3D rotation matrix around the Y axis from the given angle.
    /// @param angle The angle in radians.
    [[nodiscard]]
    static Matrix4x4 RotationMatrix3DY(const float angle);
    /// @brief Creates a 3D rotation matrix around the Y axis from the given angle.
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    [[nodiscard]]
    static Matrix4x4 RotationMatrix3DY(const float cos, const float sin);
    /// @brief Creates a 3D rotation matrix around the Z axis from the given angle.
    /// @param angle The angle in radians.
    [[nodiscard]]
    static Matrix4x4 RotationMatrix3DZ(const float angle);
    /// @brief Creates a 3D rotation matrix around the Z axis from the given angle.
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    [[nodiscard]]
    static Matrix4x4 RotationMatrix3DZ(const float cos, const float sin);
    /// @brief Creates a 3D rotation matrix from the given angle for each of the x, y, and z axis.
    [[nodiscard]]
    static Matrix4x4 RotationMatrix3D(const Vector3& rotation);
    /// @brief Creates a 3D rotation matrix from the given cosine, sine and axis.
    /// @param cos The cosine of the angle in radians.
    /// @param sin The sine of the angle in radians.
    [[nodiscard]]
    static Matrix4x4 RotationMatrix3D(const float cos, const float sin, const Vector3& axis);
    /// @brief Creates a 3D scaling matrix from the given Vector3.
    [[nodiscard]]
    static Matrix4x4 ScalingMatrix3D(const Vector3& scale);
    /// @brief Creates a Translation-Rotation-Scaling (TRS) matrix from the given translation, rotation and scaling.
    [[nodiscard]]
    static Matrix4x4 TRS(const Vector3& translation, const Vector3& rotation, const Vector3& scale);
    /// @brief Creates a Translation-Rotation-Scaling (TRS) matrix from the given translation, rotation and scaling.
    /// @param rotationAngle The angle in radians.
    [[nodiscard]]
    static Matrix4x4 TRS(const Vector3& translation, const float rotationAngle, const Vector3& axis, const Vector3& scale);
    /// @brief Creates a Translation-Rotation-Scaling (TRS) matrix from the given translation, rotation and scaling.
    [[nodiscard]]
    static Matrix4x4 TRS(const Vector3& translation, const Matrix4x4& rotation, const Vector3& scale);

    [[nodiscard]]
    Quaternion ToQuaternion() const;

    static Matrix4x4 ViewMatrix(const Vector3& Eye, const Vector3& center, const Vector3& Up);
    static Matrix4x4 ProjectionMatrix(const float fovY, const float aspectRatio, const float zNear, const float zFar);

    [[nodiscard]]
    constexpr const Vector4& operator[](const size_t row) const;
    [[nodiscard]]
    constexpr Vector4& operator[](const size_t row);
    explicit operator Vector3() const;
    explicit operator Vector4() const;
    explicit operator Vector() const;
    operator Matrix2x2() const;
    operator Matrix3x3() const;
    operator Matrix() const;

    // Automatically generates all comparison operators
    [[nodiscard]]
    friend auto operator<=>(const Matrix4x4& a, const Matrix4x4& b) = default;

private:
    Vector4 r0, r1, r2, r3;
};

[[nodiscard]]
Matrix4x4 operator-(const Matrix4x4& matrix);
[[nodiscard]]
Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2);
[[nodiscard]]
Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2);
[[nodiscard]]
Matrix4x4 operator*(const Matrix4x4& m, const float scalar);
[[nodiscard]]
Vector4 operator*(const Matrix4x4& m, const Vector4& v);
[[nodiscard]]
Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2);

Matrix4x4& operator+=(Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4& operator-=(Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4& operator*=(Matrix4x4& m, const float scalar);
Matrix4x4& operator*=(Matrix4x4& m1, const Matrix4x4& m2);

std::ostream& operator<<(std::ostream& out, const Matrix4x4& m);