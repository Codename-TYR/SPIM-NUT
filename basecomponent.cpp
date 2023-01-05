#include "basecomponent.h"
#include "actor.h"

BaseComponent::BaseComponent()
{

}

BaseComponent::BaseComponent(Actor* InOwner)
    :mOwner {InOwner}
{

}

Actor *BaseComponent::GetOwner(BaseComponent *InChild)
{
    if (mOwner)
    {
        return mOwner;
    }
    return nullptr;
}
