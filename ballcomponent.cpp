#include "ballcomponent.h"
#include "actor.h"

BallComponent::BallComponent()
{
    CollisionVolumeType = ECollisionVolume ::ECV_Sphere;
    InitializeComponentType();
    SetAsSphereCollider(0.25);
}

void BallComponent::ComponentTick(float deltaTime)
{
    mParentActor->mPosRotScale.translate(mVelocity * deltaTime);

    for (unsigned int i = 0; i < mAllWalls->size(); i++) {
            CollisionEvent collisionEvent = CollisionComponent::IsSphereCollidingWithBox(this, mAllWalls->at(i));
            if (collisionEvent.isCollision) {
                mVelocity = mVelocity - 2 * (QVector3D::dotProduct(mVelocity, collisionEvent.direction)) * collisionEvent.direction * 0.1;
                mVelocity = mVelocity + (collisionEvent.direction * collisionEvent.distance) / (deltaTime * 2) ;
            }
    }

    mVelocity = mVelocity * 0.99;
    mVelocity = mVelocity + (QVector3D{0,0,-9.81} * deltaTime);
}

void BallComponent::DrawComponent()
{

}

void BallComponent::GiveAccessToWalls(std::vector<CollisionComponent *> *walls)
{
    mAllWalls = walls;
}

void BallComponent::InitializeComponentType()
{
    ComponentType = EComponentType::ECT_BallComponent;
}

void BallComponent::AddForce(QVector3D force)
{

}

void BallComponent::AddForce(QVector3D direction, float multiplier)
{

}
