#ifndef BALLCOMPONENT_H
#define BALLCOMPONENT_H

#include "collisioncomponent.h"
#include "qvectornd.h"


class BallComponent : public CollisionComponent
{
public:
    BallComponent();

    void ComponentTick() override {};

private:
    void InitializeComponentType() override {ComponentType = EComponentType::ECT_BallComponent;}


public:
    QVector3D GetVelocity();

    void AddForce(QVector3D force);
    void AddForce(QVector3D direction, float multiplier);

private:
    float mMass {0.0f};
    QVector3D mVelocity;



};

#endif // BALLCOMPONENT_H
