#include "trianglecollider.h"

TriangleCollider::TriangleCollider(const QVector3D& v1, const QVector3D& v2, const QVector3D& v3)
{
    mColliderType = Triangle;
    mTrianglePoints[0] = v1;
    mTrianglePoints[1] = v2;
    mTrianglePoints[2] = v3;

    mVertices.push_back(Vertex(v1, {1,1,1}));
    mVertices.push_back(Vertex(v2, {1,1,1}));
    mVertices.push_back(Vertex(v3, {1,1,1}));

    mIndices.push_back(0);
    mIndices.push_back(1);
    mIndices.push_back(2);
}

QVector3D TriangleCollider::GetCollisionDirectionFromTarget(ColliderBase *source)
{
    return GetNormalFromPoints(mTrianglePoints[0], mTrianglePoints[1], mTrianglePoints[2]);
}

bool TriangleCollider::EvaluateIfPointIsInsideTriangle(const QVector3D &pt)
{
    const QVector3D baryc = Barycentric(pt, mTrianglePoints[0], mTrianglePoints[1], mTrianglePoints[2]);
    return isOverlappingTriangle(baryc);
}
