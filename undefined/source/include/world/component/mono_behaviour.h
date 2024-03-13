#pragma once
#include "world/component/component.h"


class MonoBehaviour : public Component
{
public:
	UNDEFINED_ENGINE void Accept(Visitor* visitor);

	UNDEFINED_ENGINE virtual void Start();

	UNDEFINED_ENGINE virtual void Update();

	UNDEFINED_ENGINE virtual void FixedUpdate();

	UNDEFINED_ENGINE virtual void LateUpdate();

	UNDEFINED_ENGINE virtual void OnEnable();

	UNDEFINED_ENGINE virtual void OnDisable();

	UNDEFINED_ENGINE virtual void OnCollisionEnter();

	UNDEFINED_ENGINE virtual void OnCollisionStay();

	UNDEFINED_ENGINE virtual void OnCollisionExit();

	UNDEFINED_ENGINE virtual void OnDestroy();

private:

};

