#pragma once

#include "utils/flag.h"

//#include "world/components/transform.h"

class Object;
class Transform;

class Component
{
public:
	virtual ~Component() {};

	void Enable();
	void Disable();
	const bool IsEnable() const;

	const Object* GetObject() const;
	const Transform* GetTransform() const;

	virtual void Awake() {};

	virtual void Start() {};

	virtual void FixedUpdate() {};

	virtual void Update() {};

	virtual void LateUpdate() {};

	virtual void Draw() {};

	virtual void OnEnable() {};

	virtual void OnDisable() {};

private:
	
	Object* mObject;

	Transform* mTransform;

	bool isEnable = true;

};