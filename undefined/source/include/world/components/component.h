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

	Object& GetObject();
	Transform& GetTransform();
	const Transform& GetTransform() const;

	virtual void Start() {};

	virtual void FixedUpdate() {};

	virtual void Update() {};

	virtual void LateUpdate() {};

	virtual void Draw() {};

	virtual void OnEnable() {};

	virtual void OnDisable() {};

private:
	
	std::shared_ptr<Object> mObject;

	bool mIsEnable = true;

};