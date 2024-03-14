#pragma once

#include "utils/flag.h"

class Visitor;

class Component
{
public:
	virtual ~Component() {};

	virtual void Accept(Visitor& visitor) = 0;
private:

};