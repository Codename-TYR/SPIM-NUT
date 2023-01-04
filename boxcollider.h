#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "colliderbase.h"
#include <QVector3D>

class BoxCollider : public ColliderBase
{
public:
    BoxCollider(const QVector3D& pos, const QVector3D& size);
    QVector3D GetCollisionDirectionFromTarget(ColliderBase *source);
    QVector3D GetUpDirection();
    QVector3D GetForwardDirection();
    QVector3D GetRightDirection();
    std::vector<QVector3D> GetAllPoints();
    void SATCollisionCheck(BoxCollider *target);
    std::pair<bool, float> IsPointsOnAxisOverlapping(QVector3D axis, BoxCollider *target);
private:
    QVector3D mPosition;
    QVector3D mSize;
};

#endif // BOXCOLLIDER_H
