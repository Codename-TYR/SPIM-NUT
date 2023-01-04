#include "boxcollider.h"

BoxCollider::BoxCollider(const QVector3D& pos, const QVector3D& size)
{
    mSize = size;
    mPosition = pos;
    mMatrix.translate(pos);
    mColliderType = ColliderType::Box;
    mVertices.push_back(Vertex({0,0,0}, {1,1,1}));
    mVertices.push_back(Vertex(QVector3D{size.x(), 0, 0}, {1,1,1}));
    mVertices.push_back(Vertex(QVector3D{size.x(), size.y(), 0}, {1,1,1}));
    mVertices.push_back(Vertex(QVector3D{0, size.y(), 0}, {1,1,1}));

    mVertices.push_back(Vertex(QVector3D{0,0,size.z()}, {1,1,1}));
    mVertices.push_back(Vertex(QVector3D{size.x(), 0, size.z()}, {1,1,1}));
    mVertices.push_back(Vertex(QVector3D{size.x(), size.y(), size.z()}, {1,1,1}));
    mVertices.push_back(Vertex(QVector3D{0, size.y(), size.z()}, {1,1,1}));

    mIndices.push_back(0);
    mIndices.push_back(1);
    mIndices.push_back(2);
    mIndices.push_back(3);
    mIndices.push_back(0);
    mIndices.push_back(4);
    mIndices.push_back(5);
    mIndices.push_back(1);
    mIndices.push_back(5);
    mIndices.push_back(6);
    mIndices.push_back(2);
    mIndices.push_back(6);
    mIndices.push_back(7);
    mIndices.push_back(3);
    mIndices.push_back(7);
    mIndices.push_back(4);
}


QVector3D BoxCollider::GetCollisionDirectionFromTarget(ColliderBase* source)
{

}

QVector3D BoxCollider::GetUpDirection()
{
    QVector3D up = QVector3D(0,0,mSize.z());
    up = mMatrix.mapVector(up);
    return up;
}

QVector3D BoxCollider::GetForwardDirection()
{
    QVector3D fwd = QVector3D(0,mSize.y(),0);
    fwd = mMatrix.mapVector(fwd);
    return fwd;
}

QVector3D BoxCollider::GetRightDirection()
{
    QVector3D right = QVector3D(mSize.x(),0,0);
    right = mMatrix.mapVector(right);
    return right;
}

std::vector<QVector3D> BoxCollider::GetAllPoints()
{
    QVector3D pos;
    pos = mMatrix.map(pos);

    std::vector<QVector3D> out;
    out.reserve(8);
    out.push_back(pos);
    out.push_back(pos + GetRightDirection());
    out.push_back(pos + GetRightDirection() + GetForwardDirection());
    out.push_back(pos + GetForwardDirection());

    out.push_back(pos + GetUpDirection());
    out.push_back(pos + GetRightDirection() + GetUpDirection());
    out.push_back(pos + GetRightDirection() + GetForwardDirection() + GetUpDirection());
    out.push_back(pos + GetForwardDirection() + GetUpDirection());
    return out;
}

void BoxCollider::SATCollisionCheck(BoxCollider* target)
{
    std::vector<std::pair<QVector3D, float>> collisionAxisAndScalars;
    std::pair<QVector3D, float> putInVector;
    // My X axis
    QVector3D myXaxis = GetRightDirection();
    std::pair<bool, float> overlapTestResult = IsPointsOnAxisOverlapping(myXaxis, target);
    if (!overlapTestResult.first == true) {
        return;
    }
    putInVector.first = myXaxis;
    putInVector.second = overlapTestResult.second;
    collisionAxisAndScalars.push_back(putInVector);

    QVector3D myYaxis = GetForwardDirection();
    overlapTestResult = IsPointsOnAxisOverlapping(myYaxis, target);
    if (!overlapTestResult.first == true) {
        return;
    }
    putInVector.first = myYaxis;
    putInVector.second = overlapTestResult.second;
    collisionAxisAndScalars.push_back(putInVector);

    QVector3D myZaxis = GetUpDirection();
    overlapTestResult = IsPointsOnAxisOverlapping(myZaxis, target);
    if (!overlapTestResult.first == true) {
        return;
    }
    putInVector.first = myZaxis;
    putInVector.second = overlapTestResult.second;
    collisionAxisAndScalars.push_back(putInVector);


    QVector3D targetXaxis = target->GetRightDirection();
    overlapTestResult = IsPointsOnAxisOverlapping(targetXaxis, target);
    if (!overlapTestResult.first == true) {
        return;
    }
    putInVector.first = targetXaxis;
    putInVector.second = overlapTestResult.second;
    collisionAxisAndScalars.push_back(putInVector);

    QVector3D targetYaxis = target->GetForwardDirection();
    overlapTestResult = IsPointsOnAxisOverlapping(targetYaxis, target);
    if (!overlapTestResult.first == true) {
        return;
    }
    putInVector.first = targetYaxis;
    putInVector.second = overlapTestResult.second;
    collisionAxisAndScalars.push_back(putInVector);

    QVector3D targetZaxis = target->GetUpDirection();
    overlapTestResult = IsPointsOnAxisOverlapping(targetZaxis, target);
    if (!overlapTestResult.first == true) {
        return;
    }
    putInVector.first = targetZaxis;
    putInVector.second = overlapTestResult.second;
    collisionAxisAndScalars.push_back(putInVector);

    float smallestDistance = collisionAxisAndScalars[0].second;
    QVector3D directionToPush = collisionAxisAndScalars[0].first;
    for (int i = 1; i < collisionAxisAndScalars.size(); i++) {
        if (std::abs(smallestDistance) > std::abs(collisionAxisAndScalars[i].second)) {
            smallestDistance = collisionAxisAndScalars[i].second;
            directionToPush = collisionAxisAndScalars[i].first;
        }
    }
    std::cout << smallestDistance << std::endl;
    target->mMatrix.translate(directionToPush.normalized() * smallestDistance * -1);

    SetColorToRedThisTick();
    target->SetColorToRedThisTick();

}

std::pair<bool, float> BoxCollider::IsPointsOnAxisOverlapping(QVector3D axis, BoxCollider* target)
{
    const std::vector<QVector3D> myPoints = GetAllPoints();
    const std::vector<QVector3D> targetPoints = target->GetAllPoints();

    std::pair<float, float> targetXAxisMinMax;
    std::pair<float, float> myXAxisMinMax;

    float crossproduct = QVector3D::dotProduct(axis, targetPoints[0]);

    targetXAxisMinMax.first = crossproduct;
    targetXAxisMinMax.second = crossproduct;

    crossproduct = QVector3D::dotProduct(axis, myPoints[0]);
    myXAxisMinMax.first = crossproduct;
    myXAxisMinMax.second = crossproduct;

    for (int i = 1; i < 8; i++) {
        crossproduct = QVector3D::dotProduct(axis, targetPoints[i]);
        targetXAxisMinMax.first = std::min(crossproduct, targetXAxisMinMax.first); // a
        targetXAxisMinMax.second = std::max(crossproduct, targetXAxisMinMax.second); // c

        crossproduct = QVector3D::dotProduct(axis, myPoints[i]);
        myXAxisMinMax.first = std::min(crossproduct, myXAxisMinMax.first); // b
        myXAxisMinMax.second = std::max(crossproduct, myXAxisMinMax.second); // d
    }

    std::pair<bool, float> out;

    if (targetXAxisMinMax.first > myXAxisMinMax.second || targetXAxisMinMax.second < myXAxisMinMax.first) {
        //no collision on this axis
        out.first = false;
        out.second = 0.f;
        return out;
    }
    out.first = true;

    float firstOverlapCheck = targetXAxisMinMax.first - myXAxisMinMax.second;
    float secondOverlapCheck = targetXAxisMinMax.second - myXAxisMinMax.first;
    if (std::abs(firstOverlapCheck) < std::abs(secondOverlapCheck)) {
        out.second = firstOverlapCheck;
    } else {
        out.second = secondOverlapCheck;
    }

    return out;
}

