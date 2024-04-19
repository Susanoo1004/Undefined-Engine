#pragma once
#include "utils/flag.h"

#include <toolbox/Vector3.h>
#include <toolbox/Matrix4x4.h>
#include <refl.hpp>
#include "reflection/attributes.h"

class Transform
{
public:

	UNDEFINED_ENGINE const Matrix4x4& LocalMatrix();
	UNDEFINED_ENGINE const Matrix4x4& WorldMatrix();

	__declspec(property(get = GetPosition, put = SetPosition)) Vector3 Position;
	UNDEFINED_ENGINE Vector3 GetPosition();
	UNDEFINED_ENGINE void SetPosition(Vector3 newPosition);

	__declspec(property(get = GetRotation, put = SetRotation)) Vector3 Rotation;
	UNDEFINED_ENGINE Vector3 GetRotation();
	UNDEFINED_ENGINE void SetRotation(Vector3 newRotation);
	__declspec(property(get = GetRotationRad, put = SetRotationRad)) Vector3 RotationRad;
	UNDEFINED_ENGINE Vector3 GetRotationRad();
	UNDEFINED_ENGINE void SetRotationRad(Vector3 newRotationRad);

	__declspec(property(get = GetScale, put = SetScale)) Vector3 Scale;
	UNDEFINED_ENGINE Vector3 GetScale();
	UNDEFINED_ENGINE void SetScale(Vector3 newScale);

	__declspec(property(get = GetLocalPosition, put = SetLocalPosition)) Vector3 LocalPosition;
	UNDEFINED_ENGINE Vector3 GetLocalPosition();
	UNDEFINED_ENGINE void SetLocalPosition(Vector3 newLocalPosition);

	__declspec(property(get = GetLocalRotation, put = SetLocalRotation)) Vector3 LocalRotation;
	UNDEFINED_ENGINE Vector3 GetLocalRotation();
	UNDEFINED_ENGINE void SetLocalRotation(Vector3 newLocalRotation);
	__declspec(property(get = GetLocalRotationRad, put = SetLocalRotationRad)) Vector3 LocalRotationRad;
	UNDEFINED_ENGINE Vector3 GetLocalRotationRad();
	UNDEFINED_ENGINE void SetLocalRotationRad(Vector3 newLocalRotationRad);

	__declspec(property(get = GetLocalScale, put = SetLocalScale)) Vector3 LocalScale;
	UNDEFINED_ENGINE Vector3 GetLocalScale();
	UNDEFINED_ENGINE void SetLocalScale(Vector3 newLocalScale);

private:
	bool mHasChanged;
	Vector3 mPosition;
	Vector3 mRotation;
	Vector3 mScale = { 1, 1, 1 };

	Vector3 mLocalPosition;
	Vector3 mLocalRotation;
	Vector3 mLocalScale = { 1, 1, 1 };

	Matrix4x4 mWorldTRS = Matrix4x4::TRS({ 0,0,0 }, { 0,0,0 }, { 1,1,1 });
	Matrix4x4 mLocalTRS = Matrix4x4::TRS({ 0,0,0 }, { 0,0,0 }, { 1,1,1 });
	friend class Object;
	friend struct refl_impl::metadata::type_info__ <Transform>;
	Transform* mParentTransform;
};

REFL_AUTO(type(Transform),
	field(mPosition, NotifyChange(&Transform::mHasChanged), Spacing(ImVec2(0, 20))),
	field(mRotation, NotifyChange(&Transform::mHasChanged), ToDeg()),
	field(mScale, NotifyChange(&Transform::mHasChanged))
)