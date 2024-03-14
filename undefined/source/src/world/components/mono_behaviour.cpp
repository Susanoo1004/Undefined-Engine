#include "world/components/mono_behaviour.h"
#include "world/components/visitor.h"

void MonoBehaviour::Accept(Visitor& visitor)
{
	visitor.Visit(*this);
}
