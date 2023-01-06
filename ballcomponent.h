#ifndef BALLCOMPONENT_H
#define BALLCOMPONENT_H

#include "collisioncomponent.h"
#include "qvectornd.h"


class BallComponent : public CollisionComponent
{
public:
    BallComponent();

    void ComponentTick(float deltaTime) override;
    void DrawComponent() override;

    void GiveAccessToWalls(std::vector<CollisionComponent*>* walls);

private:
    void InitializeComponentType() override;

    class Sound* s{nullptr};

    float mTimeSincePlayedSound{0.f};


public:
    QVector3D GetVelocity();

    static BallComponent* GetPointerToBall();



    void AddForce(QVector3D force);
    void AddForce(QVector3D direction, float multiplier);

    void OnCollideWithWall(float force);
    QVector3D GetPosition();
    void Jump(float strength);
private:
    float mMass {1.0f};
    QVector3D mVelocity;
    std::vector<CollisionComponent*>* mAllWalls;
    static inline BallComponent* activeBall;
    QVector3D mLastCollision;

    void ForceMovement(QVector3D movement);
};

#endif // BALLCOMPONENT_H
