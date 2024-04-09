#include "world/scene_manager/transform.h"

#include <cmath>
#include <toolbox/Matrix3x3.h>
#include <toolbox/Quaternion.h>
#include <toolbox/Calc.h>


const Matrix4x4& Transform::WorldToLocalMatrix() const
{
	return mLocalTRS;
}

const Matrix4x4& Transform::LocalToWorldMatrix() const
{
	if (mParentTransform)
	{
		return mLocalTRS * mParentTransform->LocalToWorldMatrix();
	}
	return mLocalTRS;
}

Vector3 Transform::GetPosition()
{
	Matrix4x4 trs = LocalToWorldMatrix();
	return { trs[0][3], trs[1][3], trs[2][3] };
}

void Transform::SetPosition(Vector3 newPosition)
{
	mLocalTRS = Matrix4x4::TRS(newPosition, GetRotationRad(), GetScale());

	if (mParentTransform)
	{
		mLocalTRS *= Matrix4x4::Inverse(mParentTransform->LocalToWorldMatrix());
	}

	mLocalPosition = { mLocalTRS[0][3], mLocalTRS[1][3], mLocalTRS[2][3] };
}

Vector3 Transform::GetRotation()
{
	Matrix4x4 trs = LocalToWorldMatrix();

	float sy = std::sqrt(trs[0][0] * trs[0][0] + trs[1][0] * trs[1][0]);
	bool singular = sy < 1e-6; // If

	float x, y, z;
	if (!singular)
	{
		x = std::atan2(trs[2][1], trs[2][2]);
		y = std::atan2(-trs[2][0], sy);
		z = std::atan2(trs[1][0], trs[0][0]);
	}
	else
	{
		x = std::atan2(-trs[1][2], trs[1][1]);
		y = std::atan2(-trs[2][0], sy);
		z = 0;
	}
	return { calc::ToDeg(x), calc::ToDeg(y), calc::ToDeg(z) };
}

void Transform::SetRotation(Vector3 newRotation)
{
	mLocalTRS = Matrix4x4::TRS(GetPosition(), { calc::ToRad(newRotation.x), calc::ToRad(newRotation.y), calc::ToRad(newRotation.z) }, GetScale());

	if (mParentTransform)
	{
		mLocalTRS *= Matrix4x4::Inverse(mParentTransform->LocalToWorldMatrix());
	}

	float scalingFactor = std::sqrt(mLocalTRS[0][0] * mLocalTRS[0][0] + mLocalTRS[0][1] * mLocalTRS[0][1] + mLocalTRS[0][2] * mLocalTRS[0][2]);
	Matrix3x3 rotMat = (1.f / scalingFactor) * Matrix3x3(mLocalTRS);
	float sy = std::sqrt(rotMat[0][0] * rotMat[0][0] + rotMat[1][0] * rotMat[1][0]);

	float x, y, z;
	if (!calc::IsZero(sy))
	{
		x = std::atan2(rotMat[2][1], rotMat[2][2]);
		y = std::atan2(-rotMat[2][0], sy);
		z = std::atan2(rotMat[1][0], rotMat[0][0]);
	}
	else
	{
		x = std::atan2(-rotMat[1][2], rotMat[1][1]);
		y = std::atan2(-rotMat[2][0], sy);
		z = 0;
	}
	x = std::fmodf(x, 2.f * calc::PI);
	y = std::fmodf(y, 2.f * calc::PI);
	z = std::fmodf(z, 2.f * calc::PI);

	mLocalRotation = { x, y, z };
}

Vector3 Transform::GetRotationRad()
{
	Matrix4x4 trs = LocalToWorldMatrix();

	float scalingFactor = std::sqrt(trs[0][0] * trs[0][0] + trs[0][1] * trs[0][1] + trs[0][2] * trs[0][2]);
	float sy = std::sqrt(trs[0][0] * trs[0][0] + trs[1][0] * trs[1][0]);
	bool singular = sy < 1e-6; // If

	float x, y, z;
	if (!calc::IsZero(sy))
	{
		x = std::atan2(trs[2][1], trs[2][2]);
		y = std::atan2(-trs[2][0], scalingFactor);
		z = std::atan2(trs[1][0], trs[0][0]);
	}
	else
	{
		x = std::atan2(-trs[1][2], trs[1][1]);
		y = std::atan2(-trs[2][0], scalingFactor);
		z = 0;
	}
	return { x, y, z };
}

void Transform::SetRotationRad(Vector3 newRotationRad)
{
	mLocalTRS = Matrix4x4::TRS(GetPosition(), { newRotationRad.x, newRotationRad.y, newRotationRad.z }, GetScale());

	if (mParentTransform)
	{
		mLocalTRS *= Matrix4x4::Inverse(mParentTransform->LocalToWorldMatrix());
	}

	float scalingFactor = std::sqrt(mLocalTRS[0][0] * mLocalTRS[0][0] + mLocalTRS[0][1] * mLocalTRS[0][1] + mLocalTRS[0][2] * mLocalTRS[0][2]);
	Matrix3x3 rotMat = (1.f / scalingFactor) * Matrix3x3(mLocalTRS);
	float sy = std::sqrt(rotMat[0][0] * rotMat[0][0] + rotMat[1][0] * rotMat[1][0]);

	float x, y, z;
	if (!calc::IsZero(sy))
	{
		x = std::atan2(rotMat[2][1], rotMat[2][2]);
		y = std::atan2(-rotMat[2][0], sy);
		z = std::atan2(rotMat[1][0], rotMat[0][0]);
	}
	else
	{
		x = std::atan2(-rotMat[1][2], rotMat[1][1]);
		y = std::atan2(-rotMat[2][0], sy);
		z = 0;
	}
	x = std::fmodf(x, 2.f * calc::PI);
	y = std::fmodf(y, 2.f * calc::PI);
	z = std::fmodf(z, 2.f * calc::PI);

	mLocalRotation = { x, y, z };
}

Vector3 Transform::GetScale()
{
	Matrix4x4 trs = LocalToWorldMatrix();

	//// gram_schimdt orthoNormalization
	Matrix3x3 orthoNormal = trs;

	for (int i = 1; i < 3; i++) 
	{
		for (int j = 0; j < i; j++) 
{
			double scaling_factor = Vector3::Dot(orthoNormal[j], orthoNormal[i])
									/ Vector3::Dot(orthoNormal[j], orthoNormal[j]);

			// Subtract each scaled component of orthoNormal_j from orthoNormal_i
			for (int k = 0; k < 3; k++)
			{
				orthoNormal[i][k] -= scaling_factor * orthoNormal[j][k];
			}
		}
	}

	// Now normalize all the 'n' orthogonal vectors
	for (int i = 0; i < 3; i++)
	{
		orthoNormal[i] = orthoNormal[i].Normalized();
	}
	///////


	return Vector3((Matrix3x3(trs) * Matrix3x3::Inverse(orthoNormal)) * Vector3(1, 1, 1));
}

void Transform::SetScale(Vector3 newScale)
{
	mLocalTRS = Matrix4x4::TRS(GetPosition(), GetRotationRad(), newScale);

	if (mParentTransform)
	{
		mLocalTRS *= Matrix4x4::Inverse(mParentTransform->LocalToWorldMatrix());
	}

	//// gram_schimdt orthoNormalization
	Matrix3x3 orthoNormal = mLocalTRS;

	for (int i = 1; i < 3; i++) {
		for (int j = 0; j < i; j++) {
			double scaling_factor = Vector4::Dot(orthoNormal[j], orthoNormal[i])
				/ Vector4::Dot(orthoNormal[j], orthoNormal[j]);

			// Subtract each scaled component of orthoNormal_j from orthoNormal_i
			for (int k = 0; k < 3; k++)
			{
				orthoNormal[i][k] -= scaling_factor * orthoNormal[j][k];
			}
		}
	}

	// Now normalize all the 'n' orthogonal vectors
	for (int i = 0; i < 3; i++)
	{
		orthoNormal[i] = orthoNormal[i].Normalized();
	}
	///////
	mLocalScale = Vector3((Matrix3x3(mLocalTRS) * Matrix3x3::Inverse(orthoNormal)) * Vector3(1, 1, 1));
}

Vector3 Transform::GetLocalPosition()
{
	return mLocalPosition;
}

void Transform::SetLocalPosition(Vector3 newLocalPosition)
{
	mLocalTRS = Matrix4x4::TRS(newLocalPosition, mLocalRotation, mLocalScale);
	mLocalPosition = newLocalPosition;
}

Vector3 Transform::GetLocalRotation()
{
	return { calc::ToDeg(mLocalRotation.x), calc::ToDeg(mLocalRotation.y), calc::ToDeg(mLocalRotation.z) };
}

void Transform::SetLocalRotation(Vector3 newLocalRotation)
{
	newLocalRotation.x = calc::ToRad(std::fmodf(newLocalRotation.x, 2.f * calc::PI));
	newLocalRotation.y = calc::ToRad(std::fmodf(newLocalRotation.y, 2.f * calc::PI));
	newLocalRotation.z = calc::ToRad(std::fmodf(newLocalRotation.z, 2.f * calc::PI));
	mLocalTRS = Matrix4x4::TRS(mLocalPosition, newLocalRotation, mLocalScale);
	mLocalRotation = newLocalRotation;
}

Vector3 Transform::GetLocalRotationRad()
{
	return mLocalRotation;
}

void Transform::SetLocalRotationRad(Vector3 newLocalRotationRad)
{
	newLocalRotationRad.x = std::fmodf(newLocalRotationRad.x, 2.f * calc::PI);
	newLocalRotationRad.y = std::fmodf(newLocalRotationRad.y, 2.f * calc::PI);
	newLocalRotationRad.z = std::fmodf(newLocalRotationRad.z, 2.f * calc::PI);
	mLocalTRS = Matrix4x4::TRS(mLocalPosition, newLocalRotationRad, mLocalScale);
	mLocalRotation = newLocalRotationRad;
}

Vector3 Transform::GetLocalScale()
{
	return mLocalScale;
}

void Transform::SetLocalScale(Vector3 newLocalScale)
{
	mLocalTRS = Matrix4x4::TRS(mLocalPosition, mLocalRotation, newLocalScale);
	mLocalScale = newLocalScale;
}
