#pragma once

#include "world/components/component.h"

class MonoBehaviour : public Component
{
public:

	virtual void Start();

	virtual void Update();

	virtual void FixedUpdate();

	virtual void LateUpdate();

	virtual void OnEnable();

	virtual void OnDisable();

	virtual void OnCollisionEnter();

	virtual void OnCollisionStay();

	virtual void OnCollisionExit();

	virtual void OnDestroy();
};

