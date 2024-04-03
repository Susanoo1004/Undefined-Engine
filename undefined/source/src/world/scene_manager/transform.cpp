#include "world/scene_manager/transform.h"
#include <toolbox/Quaternion.h>


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
	mLocalTRS = Matrix4x4::TRS(newPosition /* * something */, GetLocalRotation(), GetLocalScale());
}

Vector3 Transform::GetRotation()
{
	return Vector3();
}

void Transform::SetRotation(Vector3 newRotation)
{
	//mLocalTRS = Matrix4x4::TRS(GetPosition(), newRotation /* * something */, GetScale());
}

Vector3 Transform::GetScale()
{
	Matrix4x4 trs = LocalToWorldMatrix();
	return { trs[0][0], trs[1][1], trs[2][2] };
}

void Transform::SetScale(Vector3 newScale)
{
	mLocalTRS = Matrix4x4::TRS(GetLocalPosition(), GetLocalRotation(), newScale /* * something */);
}

Vector3 Transform::GetLocalPosition()
{
	return { mLocalTRS[0][3], mLocalTRS[1][3], mLocalTRS[2][3] };
}

void Transform::SetLocalPosition(Vector3 newLocalPosition)
{
	mLocalTRS[0][3] = newLocalPosition.x;
	mLocalTRS[1][3] = newLocalPosition.y;
	mLocalTRS[2][3] = newLocalPosition.z;
	
}

Vector3 Transform::GetLocalRotation()
{
	return Vector3();
	//return mLocalRotation;
}

void Transform::SetLocalRotation(Vector3 newLocalRotation)
{
	//mLocalRotation = newLocalRotation;
}

Vector3 Transform::GetLocalScale()
{
	return { mLocalTRS[0][0], mLocalTRS[1][1], mLocalTRS[2][2] };
}

void Transform::SetLocalScale(Vector3 newLocalScale)
{
	mLocalTRS[0][3] = newLocalScale.x;
	mLocalTRS[1][3] = newLocalScale.y;
	mLocalTRS[2][3] = newLocalScale.z;
}
