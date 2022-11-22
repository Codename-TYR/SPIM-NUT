#include "planecollider.h"

PlaneCollider::PlaneCollider(const QVector3D& p1, const QVector3D& p2, const QVector3D& p3, const QVector3D& p4) : mTriangleCollider1(p1,p2,p3), mTriangleCollider2(p1,p3,p4)
{
    mColliderType = ColliderType::Plane;
}

QVector3D PlaneCollider::GetCollisionDirectionFromTarget(ColliderBase *source)
{
    const QVector3D sourcePos = source->getPosition();

    QVector3D baryc = Barycentric(sourcePos, mTriangleCollider1.mTrianglePoints[0], mTriangleCollider1.mTrianglePoints[1], mTriangleCollider1.mTrianglePoints[2]);

    if (isOverlappingTriangle(baryc)) {
        return GetNormalFromPoints(mTriangleCollider1.mTrianglePoints[0], mTriangleCollider1.mTrianglePoints[1], mTriangleCollider1.mTrianglePoints[2]);
    }

    baryc = Barycentric(sourcePos, mTriangleCollider2.mTrianglePoints[0], mTriangleCollider2.mTrianglePoints[1], mTriangleCollider2.mTrianglePoints[2]);

    if (isOverlappingTriangle(baryc)) {
        return GetNormalFromPoints(mTriangleCollider1.mTrianglePoints[0], mTriangleCollider1.mTrianglePoints[1], mTriangleCollider1.mTrianglePoints[2]);
    }

    return (GetNormalFromPoints(mTriangleCollider1.mTrianglePoints[0], mTriangleCollider1.mTrianglePoints[1], mTriangleCollider1.mTrianglePoints[2])
            +
            GetNormalFromPoints(mTriangleCollider1.mTrianglePoints[0], mTriangleCollider1.mTrianglePoints[1], mTriangleCollider1.mTrianglePoints[2]))
            /
            2;
}

bool PlaneCollider::EvaluateIfPointIsInsidePlane(const QVector3D& pt)
{
    if (mTriangleCollider1.EvaluateIfPointIsInsideTriangle(pt)) return true;
    if (mTriangleCollider2.EvaluateIfPointIsInsideTriangle(pt)) return true;
    return false;
}

void PlaneCollider::draw()
{
    mTriangleCollider1.draw();
    mTriangleCollider2.draw();
}

void PlaneCollider::init(int n)
{
    mTriangleCollider1.init(n);
    mTriangleCollider2.init(n);
}

