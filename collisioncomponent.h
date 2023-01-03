#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include "basecomponent.h"

enum ECollisionVolume
{
    ECV_Box, ECV_Sphere
};

class CollisionComponent : public BaseComponent
{
public:
    CollisionComponent();

    ECollisionVolume CollisionVolumeType {ECollisionVolume::ECV_Box};

    virtual void ComponentTick() override {};

private:
    void InitializeComponentType() override {ComponentType = EComponentType::ECT_CollisionComponent;}


};

#endif // COLLISIONCOMPONENT_H
