#ifndef ACTOR_H
#define ACTOR_H

#include <QMatrix4x4>
#include "basecomponent.h"


class Actor
{
public:
    Actor();

private:
    //class QVector3D mPosition;
    //class QVector3D mRotation;

    QMatrix4x4 mPosRotScale;

public:
    std::vector<class BaseComponent*> mComponents;

public:
    void AddComponent(BaseComponent* InComponent);

    BaseComponent* GetComponentOfType(EComponentType InComponentType);

    void Tick(float deltaTime);

    bool DisplayCollisionBoxes{false};

    friend class CollisionComponent;
    friend class BallComponent;
    friend class MeshComponent;
    void Draw();
    void SetLocation(QVector3D newPos);
    void Move(QVector3D offset);

    void Rotate(float degrees, QVector3D axis);
};

#endif // ACTOR_H
