#ifndef PLANECOLLIDER_H
#define PLANECOLLIDER_H

#include "colliderbase.h"
#include "trianglecollider.h"

class PlaneCollider : public ColliderBase
{
private:
    TriangleCollider mTriangleCollider1;
    TriangleCollider mTriangleCollider2;
public:
    PlaneCollider(const QVector3D& p1, const QVector3D& p2, const QVector3D& p3, const QVector3D& p4);
    QVector3D GetCollisionDirectionFromTarget(ColliderBase* source) override;

    bool EvaluateIfPointIsInsidePlane(const QVector3D &pt);

    void draw() override;
    void init(int n) override;
};

#endif // PLANECOLLIDER_H
