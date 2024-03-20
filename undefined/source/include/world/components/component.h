#pragma once

#include "utils/flag.h"

#include "world/components/transform.h"

class Object;

class Component
{
public:
	virtual ~Component() {};

	void Enable();
	void Disable();
	const bool IsEnable() const;
	
	virtual void Start() {};

	virtual void FixedUpdate() {};

	virtual void Update() {};

	virtual void LateUpdate() {};

	virtual void Draw() {};

	virtual void OnEnable() {};

	virtual void OnDisable() {};

	friend class ::Object;
	__declspec(property(get = GetObject, put = SetObject)) std::shared_ptr<::Object> GameObject;
	std::shared_ptr<::Object> GetObject() const { return mObject; };

	__declspec(property(get = GetTransform, put = SetTransform)) std::shared_ptr<::Transform> GameTransform;
	std::shared_ptr<::Transform> GetTransform() const { return mTransform; };


private:
	void SetObject(std::shared_ptr<::Object> newObject) { mObject = newObject; };
	void SetTransform(std::shared_ptr<::Transform> newTransform) { mTransform = newTransform; };

	bool mIsEnable = true;
	
	std::shared_ptr<::Object> mObject;
	std::shared_ptr<::Transform> mTransform;
};