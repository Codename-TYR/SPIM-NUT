#ifndef TRIANGLECOLLIDER_H
#define TRIANGLECOLLIDER_H

#include "colliderbase.h"

class TriangleCollider : public ColliderBase
{
    QVector3D mTrianglePoints[3];
public:
    TriangleCollider(const QVector3D& v1, const QVector3D& v2, const QVector3D& v3);
    QVector3D GetCollisionDirectionFromTarget(ColliderBase* source) override;
    bool EvaluateIfPointIsInsideTriangle(const QVector3D &pt);
    friend class PlaneCollider;
};

#endif // TRIANGLECOLLIDER_H
