#pragma once
#include "world/component/visitor.h"

#include "world/component/mono_behaviour.h"

class VisitorForUpdate : public Visitor
{
public:
	VisitorForUpdate();
	~VisitorForUpdate();

	void VisitUpdate(VisitorForUpdate update);

private:

};

VisitorForUpdate::VisitorForUpdate()
{
}

VisitorForUpdate::~VisitorForUpdate()
{
}