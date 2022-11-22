#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include "colliderbase.h"
class PlaneCollider;
class SphereCollider : public ColliderBase
{
public:
    SphereCollider();
    QVector3D GetCollisionDirectionFromTarget(ColliderBase* source) override;
    bool EvaluateSphereOnSphereCollision(SphereCollider *source);
    bool EvaluateSphereOnPlaneCollision(PlaneCollider *source);
};

#endif // SPHERECOLLIDER_H
