#ifndef BALLCOMPONENT_H
#define BALLCOMPONENT_H

#include "collisioncomponent.h"
#include "qvectornd.h"


class BallComponent : public CollisionComponent
{
public:
    BallComponent();

    void ComponentTick(float deltaTime) override;
    void DrawComponent() override;

    void GiveAccessToWalls(std::vector<CollisionComponent*>* walls);

private:
    void InitializeComponentType() override;


public:
    QVector3D GetVelocity();

    void AddForce(QVector3D force);
    void AddForce(QVector3D direction, float multiplier);

private:
    float mMass {1.0f};
    QVector3D mVelocity;
    std::vector<CollisionComponent*>* mAllWalls;


};

#endif // BALLCOMPONENT_H
