#include "spherecollider.h"
#include "octahedronball.h"
#include "planecollider.h"

SphereCollider::SphereCollider()
{
    mColliderType = ColliderType::Sphere;
    mVertices = OctahedronBall::oktaederUnitBall(1,{1,1,1});
    for (int i = 0; i < mVertices.size(); i++) {
        mIndices.push_back(i);
    }

}

QVector3D SphereCollider::GetCollisionDirectionFromTarget(ColliderBase *source)
{
    const QVector3D pos = source->getPosition();
    const QVector3D myPos = getPosition();
    return pos-myPos;
}

bool SphereCollider::EvaluateSphereOnSphereCollision(SphereCollider *source)
{
    const QVector3D sourcePos = source->getPosition();
    const QVector3D myPos = getPosition();
    const QVector3D difference = sourcePos-myPos;

    if (difference.lengthSquared() > 2 * 2)
    {
        return false;
    }
    SetColorToRedThisTick();
    source->SetColorToRedThisTick();
    return true;
}

bool SphereCollider::EvaluateSphereOnPlaneCollision(PlaneCollider *source)
{
    const QVector3D planeNormal = source->GetCollisionDirectionFromTarget(this);
    const QVector3D pointToTest = getPosition() - planeNormal;
    const QVector3D crossproduct = QVector3D::crossProduct(planeNormal, pointToTest);

    if (crossproduct.lengthSquared() > 1) {
        return false;
    }

    if (source->EvaluateIfPointIsInsidePlane(getPosition())) {
        SetColorToRedThisTick();
        source->SetColorToRedThisTick();
        return true;
    }

    for (int i = 0; i < mVertices.size(); i++) {
        QVector3D vertPos = mVertices[i].GetXYZ();
        vertPos = mMatrix.map(vertPos);
        if (source->EvaluateIfPointIsInsidePlane(vertPos)) {
            SetColorToRedThisTick();
            source->SetColorToRedThisTick();
            return true;
        }
    }
    return false;
}
