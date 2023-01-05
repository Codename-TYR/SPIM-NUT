#include "ballcomponent.h"
#include "actor.h"
#include "sound.h"

BallComponent::BallComponent()
{
    CollisionVolumeType = ECollisionVolume ::ECV_Sphere;
    InitializeComponentType();
    SetAsSphereCollider(0.25);
    s = new Sound();
}

void BallComponent::OnCollideWithWall(float force) {
    if (force < 0.8f) return;
    if (mTimeSincePlayedSound < 0.25f) return;
    mTimeSincePlayedSound = 0;
    force = std::min(force, 1.f);

    s->Play("Laser", "../SPIM-NUT/Assets/laser.wav", GetPosition());

    //spill av lyd her, force kan være volumet kanskje?
}

void BallComponent::ComponentTick(float deltaTime)
{
    mTimeSincePlayedSound += deltaTime;
    mParentActor->mPosRotScale.translate(mVelocity * deltaTime);

    for (unsigned int i = 0; i < mAllWalls->size(); i++) {
            CollisionEvent collisionEvent = CollisionComponent::IsSphereCollidingWithBox(this, mAllWalls->at(i));
            if (collisionEvent.isCollision) {
                QVector3D oldVelocity = mVelocity;
                mVelocity = mVelocity - 2 * (QVector3D::dotProduct(mVelocity, collisionEvent.direction)) * collisionEvent.direction * 0.1;
                //mVelocity = mVelocity + (collisionEvent.direction * collisionEvent.distance) / (deltaTime) ;
                ForceMovement(collisionEvent.direction * collisionEvent.distance);
                OnCollideWithWall(oldVelocity.lengthSquared() - mVelocity.lengthSquared());
            }
    }

    mVelocity = mVelocity * 0.99;
    mVelocity = mVelocity + (QVector3D{0,0,-9.81} * deltaTime);
}

void BallComponent::DrawComponent()
{

}

QVector3D BallComponent::GetPosition()
{
    auto pos = mParentActor->mPosRotScale.column(3);
    return QVector3D{pos.x(), pos.y(), pos.z()};
}

void BallComponent::ForceMovement(QVector3D movement)
{
    mParentActor->mPosRotScale.translate(movement);
}

void BallComponent::GiveAccessToWalls(std::vector<CollisionComponent *> *walls)
{
    mAllWalls = walls;
}

void BallComponent::InitializeComponentType()
{
    ComponentType = EComponentType::ECT_BallComponent;
}

QVector3D BallComponent::GetVelocity()
{
    return mVelocity;
}

void BallComponent::AddForce(QVector3D force)
{

}

void BallComponent::AddForce(QVector3D direction, float multiplier)
{

}
