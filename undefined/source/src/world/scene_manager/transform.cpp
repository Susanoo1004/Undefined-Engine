#include "world/scene_manager/transform.h"

#include <cmath>
#include <toolbox/Matrix3x3.h>
#include <toolbox/Quaternion.h>
#include <toolbox/Calc.h>


const Matrix4x4& Transform::LocalMatrix()
{
	if (HasChanged)
	{
		HasChanged = false;
		Matrix4x4 worldMat = Matrix4x4::TRS(mPosition, mRotation, mScale);
		if (mParentTransform)
		{
			mLocalTRS = worldMat * Matrix4x4::Inverse(mParentTransform->WorldMatrix());
		}
		else
		{
			mLocalTRS = worldMat;
		}
	}

	return mLocalTRS;
}

const Matrix4x4& Transform::WorldMatrix()
{
	if (HasChanged)
	{
		HasChanged = false;
		Matrix4x4 worldMat = Matrix4x4::TRS(mPosition, mRotation, mScale);
		if (mParentTransform)
		{
			mLocalTRS = worldMat * Matrix4x4::Inverse(mParentTransform->WorldMatrix());
		}
		else
		{
			mLocalTRS = worldMat;
		}
	}

	if (mParentTransform)
	{
		return mLocalTRS * mParentTransform->WorldMatrix();
	}
	return mLocalTRS;
}

Vector3 Transform::GetPosition()
{
	Matrix4x4 trs = WorldMatrix();
	return { trs[0][3], trs[1][3], trs[2][3] };
}

void Transform::SetPosition(Vector3 newPosition)
{
	Matrix4x4 worldMat = Matrix4x4::TRS(newPosition, GetRotationRad(), GetScale());

	if (mParentTransform)
	{
		mLocalTRS = worldMat * Matrix4x4::Inverse(mParentTransform->WorldMatrix());
	}
	else
	{
		mLocalTRS = worldMat;
	}

	mLocalPosition = { mLocalTRS[0][3], mLocalTRS[1][3], mLocalTRS[2][3] };
}

Vector3 Transform::GetRotation()
{
	Vector3 rot = GetRotationRad();

	return { calc::ToDeg(rot.x), calc::ToDeg(rot.y), calc::ToDeg(rot.z) };
}

void Transform::SetRotation(Vector3 newRotation)
{
	SetRotationRad({ calc::ToRad(newRotation.x), calc::ToRad(newRotation.y), calc::ToRad(newRotation.z) });
}

Vector3 Transform::GetRotationRad()
{
	return WorldMatrix().ToEuler();
}

void Transform::SetRotationRad(Vector3 newRotationRad)
{
	Matrix4x4 worldMat = Matrix4x4::TRS(GetPosition(), { newRotationRad.x, newRotationRad.y, newRotationRad.z }, GetScale());

	if (mParentTransform)
	{
		mLocalTRS = worldMat * Matrix4x4::Inverse(mParentTransform->WorldMatrix());
	}
	else
	{
		mLocalTRS = worldMat;
	}

	Vector3 rot = mLocalTRS.ToEuler();

	rot.x = std::fmodf(rot.x, 2.f * calc::PI);
	rot.y = std::fmodf(rot.y, 2.f * calc::PI);
	rot.z = std::fmodf(rot.z, 2.f * calc::PI);

	mLocalRotation = rot;
}

Vector3 Transform::GetScale()
{
	Matrix4x4 trs = WorldMatrix();

	//// gram_schimdt orthoNormalization
	Matrix3x3 orthoNormal = trs;

	for (int i = 1; i < 3; i++)
	{
		for (int j = 0; j < i; j++) 
{
			float scaling_factor = Vector3::Dot(orthoNormal[j], orthoNormal[i])
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
	Matrix4x4 worldMat = Matrix4x4::TRS(GetPosition(), GetRotationRad(), newScale);

	if (mParentTransform)
	{
		mLocalTRS = worldMat * Matrix4x4::Inverse(mParentTransform->WorldMatrix());
	}
	else
	{
		mLocalTRS = worldMat;
	}

	//// gram_schimdt orthoNormalization
	Matrix3x3 orthoNormal = mLocalTRS;

	for (int i = 1; i < 3; i++) 
	{
		for (int j = 0; j < i; j++) 
		{
			float scaling_factor = Vector4::Dot(orthoNormal[j], orthoNormal[i])
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
	newLocalRotation.x = std::fmodf(calc::ToRad(newLocalRotation.x), 2.f * calc::PI);
	newLocalRotation.y = std::fmodf(calc::ToRad(newLocalRotation.y), 2.f * calc::PI);
	newLocalRotation.z = std::fmodf(calc::ToRad(newLocalRotation.z), 2.f * calc::PI);
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