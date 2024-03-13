#include "world/component/mono_behaviour.h"

void MonoBehaviour::Accept(Visitor* visitor)
{
	visitor->VisitMonoBehaviour(this);
}
