#pragma once

#include <vector>

#include "utils/flag.h"

#include "world/components/component.h"
#include "world/components/transform.h"

class Object
{
public:

	void Enable();
	void Disable();
	const bool IsEnable() const;

	const Transform* GetTransform() const;

	std::vector<Component*> Components;

private:
	bool isEnable = true;

	Transform* mTransform;

};