#pragma once

#include <refl.hpp>
#include "utils/flag.h"
#include "world/scene_manager/transform.h"

class Object;

class Component
{
public:
	virtual ~Component();

	void Enable();
	void Disable();

	const bool IsEnable() const;
	
	virtual void Start();

	virtual void FixedUpdate();

	virtual void Update();

	virtual void LateUpdate();

	virtual void Draw();

	virtual void OnEnable();

	virtual void OnDisable();

	friend class Object;
	__declspec(property(get = GetObject, put = SetObject)) Object* GameObject;
	Object* GetObject() const { return mObject; };

	__declspec(property(get = GetTransform, put = SetTransform)) Transform* GameTransform;
	Transform* GetTransform() const { return mTransform; };


private:
	void SetObject(Object* newObject) { mObject = newObject; };
	void SetTransform(Transform* newTransform) { mTransform = newTransform; };

	bool mIsEnable = true;
	
	Object* mObject;
	Transform* mTransform;
};

REFL_AUTO(type(Component),
	field(mIsEnable)
);