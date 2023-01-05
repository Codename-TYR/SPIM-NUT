#ifndef ACTOR_H
#define ACTOR_H

#include "qvectornd.h"
#include "basecomponent.h"


class Actor
{
public:
    Actor();

private:
    class QVector3D mPosition;
    class QVector3D mRotation;

public:
    std::vector<class BaseComponent*> mComponents;

public:
    void AddComponent(BaseComponent* InComponent);

    BaseComponent* GetComponentOfType(EComponentType InComponentType);


};

#endif // ACTOR_H
