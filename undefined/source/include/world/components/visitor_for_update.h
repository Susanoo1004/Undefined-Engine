#pragma once
#include "world/components/visitor.h"

#include "world/components/mono_behaviour.h"

class VisitorForUpdate : public Visitor
{
public:

	void Visit(MonoBehaviour& mono_behaviour) override;

private:

};

void VisitorForUpdate::Visit(MonoBehaviour& mono_behaviour)
{
	mono_behaviour.Update();
}
