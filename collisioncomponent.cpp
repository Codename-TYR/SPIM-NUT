#include "collisioncomponent.h"
#include "octahedronball.h"
#include "actor.h"

CollisionComponent::CollisionComponent()
{
    InitializeComponentType();
}

void CollisionComponent::ComponentTick(float deltaTime)
{

}

void CollisionComponent::SetAsBoxCollider(QVector3D position, QVector3D size)
{
    CollisionVolumeType = ECollisionVolume::ECV_Box;
    mPosition = position;
    mBoxSize = size;

    std::vector<Vertex> boxvertices;
    boxvertices.push_back(Vertex({0,0,0}, {1,1,1}));
    boxvertices.push_back(Vertex(QVector3D{size.x(), 0, 0}, {1,1,1}));
    boxvertices.push_back(Vertex(QVector3D{size.x(), size.y(), 0}, {1,1,1}));
    boxvertices.push_back(Vertex(QVector3D{0, size.y(), 0}, {1,1,1}));
    boxvertices.push_back(Vertex({0,0,0}, {1,1,1}));
    boxvertices.push_back(Vertex(QVector3D{0,0,size.z()}, {1,1,1}));
    boxvertices.push_back(Vertex(QVector3D{size.x(), 0, size.z()}, {1,1,1}));
    boxvertices.push_back(Vertex(QVector3D{size.x(), 0, 0}, {1,1,1}));
    boxvertices.push_back(Vertex(QVector3D{size.x(), 0, size.z()}, {1,1,1}));
    boxvertices.push_back(Vertex(QVector3D{size.x(), size.y(), size.z()}, {1,1,1}));
    boxvertices.push_back(Vertex(QVector3D{size.x(), size.y(), 0}, {1,1,1}));
    boxvertices.push_back(Vertex(QVector3D{size.x(), size.y(), size.z()}, {1,1,1}));
    boxvertices.push_back(Vertex(QVector3D{0, size.y(), size.z()}, {1,1,1}));
    boxvertices.push_back(Vertex(QVector3D{0, size.y(), 0}, {1,1,1}));
    boxvertices.push_back(Vertex(QVector3D{0, size.y(), size.z()}, {1,1,1}));
    boxvertices.push_back(Vertex(QVector3D{0,0,size.z()}, {1,1,1}));
    mCollisionMesh = new MeshComponent(boxvertices);
    mCollisionMesh->init(0);
    mCollisionMesh->SetDrawMethod(DrawMethod::LineLoop);
}

void CollisionComponent::SetAsSphereCollider(float radius)
{
    CollisionVolumeType = ECollisionVolume::ECV_Sphere;
    mSphereRadius = radius;

    std::vector<Vertex> spherevertices = OctahedronBall::oktaederUnitBall(2,{1,1,1}, radius);
    mCollisionMesh = new MeshComponent(spherevertices);
    mCollisionMesh->init(0);
    mCollisionMesh->SetDrawMethod(DrawMethod::LineLoop);
}

void CollisionComponent::DrawComponent()
{
    if (mParentActor != nullptr) {
        mCollisionMesh->mMatrix = mParentActor->mPosRotScale;
        mCollisionMesh->mMatrix.translate(mPosition);
    }
    mCollisionMesh->DrawComponent();
}

CollisionEvent CollisionComponent::IsSphereCollidingWithBox(CollisionComponent *sphere, CollisionComponent *box)
{
    if (sphere->CollisionVolumeType != ECV_Sphere || box->CollisionVolumeType != ECV_Box)
    {
        std::cout << "invalid objects entered in isSphereCollidingWithBox method" << std::endl;
        CollisionEvent invalidObjects;
        invalidObjects.isCollision = false;
        return invalidObjects;
    }

    std::vector<CollisionEvent> out;

    std::vector<QVector3D> boxAxises;
    boxAxises.push_back(box->GetForwardDirection());
    boxAxises.push_back(box->GetRightDirection());
    boxAxises.push_back(box->GetUpDirection());

    std::vector<QVector3D> boxPoints = box->GetBoxPoints();


    for (unsigned int i = 0; i < boxAxises.size(); i++) {
        std::vector<QVector3D> RelevantSpherePoints = sphere->GetSpherePointsAccordingToAxis(boxAxises[i]);
        CollisionEvent overlap = ArePointsOnAxisOverlapping(boxAxises[i], boxPoints, RelevantSpherePoints);
        if (overlap.isCollision == false) {
            return overlap;
        }
        out.push_back(overlap);
    }

    std::vector<QVector3D> spherePoints = sphere->GetAllSpherePoints();

    for (unsigned int i = 0; i < sphere->mPreComputedSphereNormals.size(); i++) {
        CollisionEvent overlap = ArePointsOnAxisOverlapping(sphere->mPreComputedSphereNormals[i], boxPoints, spherePoints);
        if (overlap.isCollision == false) {
            return overlap;
        }
        out.push_back(overlap);
    }

    int smallestDistanceIndex = 0;

    for (unsigned int i = 1; i < out.size(); i++) {
        if (std::abs(out[i].distance) < std::abs(out[smallestDistanceIndex].distance)) {
            smallestDistanceIndex = i;
        }
    }

    return out[smallestDistanceIndex];
}

CollisionEvent CollisionComponent::ArePointsOnAxisOverlapping(QVector3D axis, std::vector<QVector3D> obj1, std::vector<QVector3D> obj2)
{
    if  (obj1.empty() || obj2.empty()) {
        std::cout << "obj1 or obj2 is empty in ArePointsOnAxisOverlapping method" << std::endl;
        CollisionEvent invalidArguements;
        invalidArguements.isCollision = false;
        return invalidArguements;
    }

    std::pair<float, float> obj1MinMax;
    std::pair<float, float> obj2MinMax;

    float dotproduct = QVector3D::dotProduct(axis, obj1[0]);
    obj1MinMax.first = dotproduct;
    obj1MinMax.second = dotproduct;

    dotproduct = QVector3D::dotProduct(axis, obj2[0]);
    obj2MinMax.first = dotproduct;
    obj2MinMax.second = dotproduct;

    for (unsigned int i = 1; i < obj1.size(); i++) {
        dotproduct = QVector3D::dotProduct(axis, obj1[i]);
        obj1MinMax.first = std::min(dotproduct, obj1MinMax.first);
        obj1MinMax.second = std::max(dotproduct, obj1MinMax.second);
    }
    for (unsigned int i = 1; i < obj2.size(); i++) {
        dotproduct = QVector3D::dotProduct(axis, obj2[i]);
        obj2MinMax.first = std::min(dotproduct, obj2MinMax.first);
        obj2MinMax.second = std::max(dotproduct, obj2MinMax.second);
    }

    CollisionEvent out;
    if (obj2MinMax.first > obj1MinMax.second || obj2MinMax.second < obj1MinMax.first) {
        out.isCollision = false;
        return out;
    }

    out.isCollision = true;

    float overlapCheck1 = obj2MinMax.first - obj1MinMax.second;
    float overlapCheck2 = obj2MinMax.second - obj1MinMax.first;

    if (std::abs(overlapCheck1) < std::abs(overlapCheck2)) {
        out.distance = overlapCheck1;
    } else {
        out.distance = overlapCheck2;
    }
    out.direction = axis.normalized() * -1;

    return out;

}

QVector3D CollisionComponent::GetUpDirection()
{
    QVector3D up = QVector3D(0,0,1);
    up = mParentActor->mPosRotScale.mapVector(up);
    return up;
}

QVector3D CollisionComponent::GetForwardDirection()
{
    QVector3D fwd = QVector3D(0,1,0);
    fwd = mParentActor->mPosRotScale.mapVector(fwd);
    return fwd;
}

QVector3D CollisionComponent::GetRightDirection()
{
    QVector3D right = QVector3D(1,0,0);
    right = mParentActor->mPosRotScale.mapVector(right);
    return right;
}

std::vector<QVector3D> CollisionComponent::GetBoxPoints()
{
    QVector3D pos = mPosition;
    pos = mParentActor->mPosRotScale.map(pos);

    std::vector<QVector3D> out;
    out.reserve(8);
    out.push_back(pos);
    out.push_back(pos + (GetRightDirection() * mBoxSize.x()));
    out.push_back(pos + (GetRightDirection() * mBoxSize.x()) + (GetForwardDirection() * mBoxSize.y()));
    out.push_back(pos + (GetForwardDirection() * mBoxSize.y()));

    out.push_back(pos + (GetUpDirection() * mBoxSize.z()));
    out.push_back(pos + (GetRightDirection() * mBoxSize.x()) + (GetUpDirection() * mBoxSize.z()));
    out.push_back(pos + (GetRightDirection() * mBoxSize.x()) + (GetForwardDirection() * mBoxSize.y()) + (GetUpDirection() * mBoxSize.z()));
    out.push_back(pos + (GetForwardDirection() * mBoxSize.y()) + (GetUpDirection() * mBoxSize.z()));
    return out;

}

std::vector<QVector3D> CollisionComponent::GetSpherePointsAccordingToAxis(QVector3D axis)
{
    QVector3D pos;
    pos = mParentActor->mPosRotScale.map(pos);

    std::vector<QVector3D> out;
    out.push_back(pos + (axis * mSphereRadius));
    out.push_back(pos - (axis * mSphereRadius));

    return out;
}

std::vector<QVector3D> CollisionComponent::GetAllSpherePoints()
{

    if (mPreComputedSpherePoints.empty()) {

        int recursionLevels = 2;
        std::vector<Vertex> mVertices;
        mVertices.reserve(3 * 8 * pow(4, recursionLevels));
        QVector3D v0{0, 0, 1}; v0 *= mSphereRadius;
        QVector3D v1{1, 0, 0}; v1 *= mSphereRadius;
        QVector3D v2{0, 1, 0}; v2 *= mSphereRadius;
        QVector3D v3{-1, 0, 0}; v3 *= mSphereRadius;
        QVector3D v4{0, -1, 0}; v4 *= mSphereRadius;
        QVector3D v5{0, 0, -1}; v5 *= mSphereRadius;

        SubDivideSphere(mPreComputedSpherePoints, v0, v1, v2, recursionLevels);
        SubDivideSphere(mPreComputedSpherePoints, v0, v2, v3, recursionLevels);
        SubDivideSphere(mPreComputedSpherePoints, v0, v3, v4, recursionLevels);
        SubDivideSphere(mPreComputedSpherePoints, v0, v4, v1, recursionLevels);
        SubDivideSphere(mPreComputedSpherePoints, v5, v2, v1, recursionLevels);
        SubDivideSphere(mPreComputedSpherePoints, v5, v3, v2, recursionLevels);
        SubDivideSphere(mPreComputedSpherePoints, v5, v4, v3, recursionLevels);
        SubDivideSphere(mPreComputedSpherePoints, v5, v1, v4, recursionLevels);
    }
    std::vector<QVector3D> out;
    out.reserve(mPreComputedSpherePoints.size());
    for (unsigned int i = 0; i < mPreComputedSpherePoints.size(); i++) {
        out.push_back(mParentActor->mPosRotScale.map(mPreComputedSpherePoints[i]));
    }

    return out;
}

void CollisionComponent::GetSubdividedSpherePoints(std::vector<QVector3D>& Points, const QVector3D& v1, const QVector3D& v2, const QVector3D& v3)
{
        QVector3D v(v1.x(), v1.y(), v1.z());
        Points.push_back(v);
        v = QVector3D{v2.x(), v2.y(), v2.z()};
        Points.push_back(v);
        v = QVector3D{v3.x(), v3.y(), v3.z()};
        Points.push_back(v);

        QVector3D cross = QVector3D::crossProduct(v2-v1, v3-v2).normalized();
        mPreComputedSphereNormals.push_back(cross);
}

void CollisionComponent::SubDivideSphere(std::vector<QVector3D>& Points, const QVector3D& a, const QVector3D& b, const QVector3D& c, int n)
{
   if (n>0) {
       QVector3D v1 = a+b; v1.normalize(); v1 *= mSphereRadius;
       QVector3D v2 = a+c; v2.normalize(); v2 *= mSphereRadius;
       QVector3D v3 = c+b; v3.normalize(); v3 *= mSphereRadius;
       SubDivideSphere(Points, a, v1, v2, n-1);
       SubDivideSphere(Points, c, v2, v3, n-1);
       SubDivideSphere(Points, b, v3, v1, n-1);
       SubDivideSphere(Points, v3, v2, v1, n-1);
   } else {
       GetSubdividedSpherePoints(Points, a, b, c);
   }
}

