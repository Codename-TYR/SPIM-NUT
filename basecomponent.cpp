#include "basecomponent.h"
#include "actor.h"

BaseComponent::BaseComponent()
{

}

void BaseComponent::SetParent(Actor *newParent)
{
    mParentActor = newParent;

}
