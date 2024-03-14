#pragma once
#include "world/components/mono_behaviour.h"

class Visitor
{
public:

	virtual void Visit(MonoBehaviour& comp) = 0;

private:

};
