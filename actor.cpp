#include "actor.h"

Actor::Actor()
{


}

void Actor::AddComponent(BaseComponent *InComponent)
{
    mComponents.push_back(InComponent);
}

BaseComponent* Actor::GetComponentOfType(EComponentType InComponentType)
{
    foreach (BaseComponent* Component, mComponents)
    {
        if (Component->GetComponentType() == InComponentType)
        {
            return Component;
        }
    }

    return nullptr;
}
