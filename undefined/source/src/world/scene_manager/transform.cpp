#include "world/scene_manager/transform.h"

#include <cmath>
#include <toolbox/Matrix3x3.h>
#include <toolbox/Quaternion.h>
#include <toolbox/Calc.h>


const Matrix4x4& Transform::LocalMatrix()
{
	if (mHasChanged)
	{
		mHasChanged = false;
		mWorldTRS = Matrix4x4::TRS(mPosition, mRotation, mScale);
		if (mParentTransform)
		{
			mLocalTRS = mWorldTRS * Matrix4x4::Inverse(mParentTransform->WorldMatrix());
		}
		else
		{
			mLocalTRS = mWorldTRS;
		}
	}

	return mLocalTRS;
}

const Matrix4x4& Transform::WorldMatrix()
{
	if (mHasChanged)
	{
		mHasChanged = false;
		mWorldTRS = Matrix4x4::TRS(mPosition, mRotation, mScale);
		if (mParentTransform)
		{
			mLocalTRS = mWorldTRS * Matrix4x4::Inverse(mParentTransform->WorldMatrix());
		}
		else
		{
			mLocalTRS = mWorldTRS;
		}
	}

	return mWorldTRS;
}

Vector3 Transform::GetPosition()
{
	return mPosition;
}

void Transform::SetPosition(Vector3 newPosition)
{
	mWorldTRS = Matrix4x4::TRS(newPosition, GetRotationRad(), GetScale());

	if (mParentTransform)
	{
		mLocalTRS = mWorldTRS * Matrix4x4::Inverse(mParentTransform->WorldMatrix());
	}
	else
	{
		mLocalTRS = mWorldTRS;
	}

	mLocalPosition = { mLocalTRS[0][3], mLocalTRS[1][3], mLocalTRS[2][3] };
	mPosition = { mWorldTRS[0][3], mWorldTRS[1][3], mWorldTRS[2][3] };
}

Vector3 Transform::GetRotation()
{
	return { calc::ToDeg(mRotation.x), calc::ToDeg(mRotation.y), calc::ToDeg(mRotation.z) };
}

void Transform::SetRotation(Vector3 newRotation)
{
	SetRotationRad({ calc::ToRad(newRotation.x), calc::ToRad(newRotation.y), calc::ToRad(newRotation.z) });
}

Vector3 Transform::GetRotationRad()
{
	return mRotation;
}

void Transform::SetRotationRad(Vector3 newRotationRad)
{
	newRotationRad.x = std::fmodf(newRotationRad.x, 2.f * calc::PI);
	newRotationRad.y = std::fmodf(newRotationRad.y, 2.f * calc::PI);
	newRotationRad.z = std::fmodf(newRotationRad.z, 2.f * calc::PI);

	mWorldTRS = Matrix4x4::TRS(GetPosition(), newRotationRad, GetScale());

	if (mParentTransform)
	{
		mLocalTRS = mWorldTRS * Matrix4x4::Inverse(mParentTransform->WorldMatrix());
	}
	else
	{
		mLocalTRS = mWorldTRS;
	}

	Vector3 localRot = mLocalTRS.ToEuler();

	mLocalRotation = localRot;

	Vector3 worldRot = mWorldTRS.ToEuler();

	mRotation = worldRot;
}

Vector3 Transform::GetScale()
{
	return mScale;
}

void Transform::SetScale(Vector3 newScale)
{
	mWorldTRS = Matrix4x4::TRS(GetPosition(), GetRotationRad(), newScale);

	if (mParentTransform)
	{
		mLocalTRS = mWorldTRS * Matrix4x4::Inverse(mParentTransform->WorldMatrix());
	}
	else
	{
		mLocalTRS = mWorldTRS;
	}
	
	Matrix3x3 trans = Matrix4x4::Transpose(mLocalTRS);
	mLocalScale = Vector3(trans[0].Norm(), trans[1].Norm(), trans[2].Norm());

	trans = Matrix4x4::Transpose(mWorldTRS);
	mScale = Vector3(trans[0].Norm(), trans[1].Norm(), trans[2].Norm());
}

Vector3 Transform::GetLocalPosition()
{
	return mLocalPosition;
}

void Transform::SetLocalPosition(Vector3 newLocalPosition)
{
	mLocalTRS = Matrix4x4::TRS(newLocalPosition, mLocalRotation, mLocalScale);

	mLocalPosition = newLocalPosition;

	if (mParentTransform)
	{
		mWorldTRS = mLocalTRS * mParentTransform->WorldMatrix();
	}
	mWorldTRS = mLocalTRS;

	mPosition = { mWorldTRS[0][3], mWorldTRS[1][3], mWorldTRS[2][3] };
}

Vector3 Transform::GetLocalRotation()
{
	return { calc::ToDeg(mLocalRotation.x), calc::ToDeg(mLocalRotation.y), calc::ToDeg(mLocalRotation.z) };
}

void Transform::SetLocalRotation(Vector3 newLocalRotation)
{
	newLocalRotation.x = calc::ToRad(newLocalRotation.x);
	newLocalRotation.y = calc::ToRad(newLocalRotation.y);
	newLocalRotation.z = calc::ToRad(newLocalRotation.z);
	SetLocalRotationRad(newLocalRotation);
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

	if (mParentTransform)
	{
		mWorldTRS = mLocalTRS * mParentTransform->WorldMatrix();
	}
	mWorldTRS = mLocalTRS;
	
	mRotation = mWorldTRS.ToEuler();
}

Vector3 Transform::GetLocalScale()
{
	return mLocalScale;
}

void Transform::SetLocalScale(Vector3 newLocalScale)
{
	mLocalTRS = Matrix4x4::TRS(mLocalPosition, mLocalRotation, newLocalScale);
	mLocalScale = newLocalScale;

	if (mParentTransform)
	{
		mWorldTRS = mLocalTRS * mParentTransform->WorldMatrix();
	}
	mWorldTRS = mLocalTRS;

	Matrix3x3 trans = Matrix4x4::Transpose(mWorldTRS);
	mScale = Vector3(trans[0].Norm(), trans[1].Norm(), trans[2].Norm());
}