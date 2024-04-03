#pragma once
#include <toolbox/Vector3.h>
#include <toolbox/Matrix4x4.h>

class Transform
{
public:

	const Matrix4x4& WorldToLocalMatrix() const;
	const Matrix4x4& LocalToWorldMatrix() const;

	__declspec(property(get = GetPosition, put = SetPosition)) Vector3 Position;
	Vector3 GetPosition();
	void SetPosition(Vector3 newPosition);

	__declspec(property(get = GetRotation, put = SetRotation)) Vector3 Rotation;
	Vector3 GetRotation();
	void SetRotation(Vector3 newRotation);

	__declspec(property(get = GetScale, put = SetScale)) Vector3 Scale;
	Vector3 GetScale();
	void SetScale(Vector3 newScale);

	__declspec(property(get = GetLocalPosition, put = SetLocalPosition)) Vector3 LocalPosition;
	Vector3 GetLocalPosition();
	void SetLocalPosition(Vector3 newLocalPosition);

	__declspec(property(get = GetLocalRotation, put = SetLocalRotation)) Vector3 LocalRotation;
	Vector3 GetLocalRotation();
	void SetLocalRotation(Vector3 newLocalRotation);

	__declspec(property(get = GetLocalScale, put = SetLocalScale)) Vector3 LocalScale;
	Vector3 GetLocalScale();
	void SetLocalScale(Vector3 newLocalScale);

private:
	/*
	Vector3 mLocalPosition;
	Vector3 mLocalRotation;
	Vector3 mLocalScale = {1, 1, 1};

	Vector3 mWorldPosition;
	Vector3 mWorldRotation;
	Vector3 mWorldScale = {1, 1, 1};
	*/

	Matrix4x4 mLocalTRS;
	//Matrix4x4 mWorldTRS;
	friend class Object;
	Transform* mParentTransform;

};