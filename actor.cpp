#include "actor.h"

Actor::Actor()
{

}

void Actor::AddComponent(BaseComponent *InComponent)
{
    mComponents.push_back(InComponent);
    InComponent->SetParent(this);
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

QVector3D Actor::GetPosition()
{
    auto pos = mPosRotScale.column(3);
    return QVector3D{pos.x(), pos.y(), pos.z()};
}

void Actor::Tick(float deltaTime)
{
    foreach (BaseComponent* Component, mComponents)
    {
        Component->ComponentTick(deltaTime);
    }
}

void Actor::Draw()
{
    foreach (BaseComponent* Component, mComponents)
    {
        if (Component->ComponentType == ECT_CollisionComponent && DisplayCollisionBoxes == false) {
            continue;
        }
        Component->DrawComponent();
    }
}

void Actor::SetLocation(QVector3D newPos)
{
    mPosRotScale(0,3) = newPos.x();
    mPosRotScale(1,3) = newPos.y();
    mPosRotScale(2,3) = newPos.z();
}

void Actor::Move(QVector3D offset)
{
    mPosRotScale(0,3) += offset.x();
    mPosRotScale(1,3) += offset.y();
    mPosRotScale(2,3) += offset.z();
}

void Actor::Rotate(float degrees, QVector3D axis)
{
    mPosRotScale.rotate(degrees, axis);
}
