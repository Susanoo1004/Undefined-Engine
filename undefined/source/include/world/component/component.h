#pragma once

#include "utils/flag.h"

#include "world/component/visitor.h"

class Component
{
public:
	UNDEFINED_ENGINE Component();
	virtual ~Component();


	bool IsEnabled;

	virtual void Accept(Visitor* visitor);
private:

};