#pragma once
#include "world/component/mono_behaviour.h"

class Visitor
{
public:
	Visitor();
	~Visitor();

	void VisitMonoBehaviour(MonoBehaviour* mB);

private:

};
