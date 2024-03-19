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

	struct Object
	{
	public:
		friend class Object;
		__declspec(property(get = Get, put = Set)) std::shared_ptr<Object> Ptr;

		const std::shared_ptr<::Object> Get() const { return mObject; };
	private:
		void Set(std::shared_ptr<Object> newPtr) { mObject = newPtr; };
		std::shared_ptr<Object> mObject;

	} Object;

private:
	bool mIsEnable = true;
};