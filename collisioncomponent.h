#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include "basecomponent.h"
#include <QVector3D>
#include "meshcomponent.h"

struct CollisionEvent {
    QVector3D direction;
    float distance;
    bool isCollision;
};

enum ECollisionVolume
{
    ECV_Box, ECV_Sphere
};

class CollisionComponent : public BaseComponent
{
public:
    CollisionComponent();

    ECollisionVolume CollisionVolumeType {ECollisionVolume::ECV_Box};

    virtual void ComponentTick(float deltaTime) override;

    void SetAsBoxCollider(QVector3D position, QVector3D size);
    void SetAsSphereCollider(float radius);

    void DrawComponent() override;

    static CollisionEvent IsSphereCollidingWithBox(CollisionComponent* sphere, CollisionComponent* box);

protected:
    QVector3D GetUpDirection();
    QVector3D GetForwardDirection();
    QVector3D GetRightDirection();
    std::vector<QVector3D> GetBoxPoints();
    std::vector<QVector3D> GetSpherePointsAccordingToAxis(QVector3D axis);
    static CollisionEvent ArePointsOnAxisOverlapping(QVector3D axis, std::vector<QVector3D> obj1, std::vector<QVector3D> obj2);
    std::vector<QVector3D> GetAllSpherePoints();
private:
    void InitializeComponentType() override {ComponentType = EComponentType::ECT_CollisionComponent;}
    QVector3D mPosition;
    QVector3D mBoxSize;
    float mSphereRadius;
    MeshComponent* mCollisionMesh;



    void GetSubdividedSpherePoints(std::vector<QVector3D> &Points, const QVector3D &v1, const QVector3D &v2, const QVector3D &v3);
    void SubDivideSphere(std::vector<QVector3D> &Points, const QVector3D &a, const QVector3D &b, const QVector3D &c, int n);

    std::vector<QVector3D> mPreComputedSpherePoints;
    std::vector<QVector3D> mPreComputedSphereNormals;
};

#endif // COLLISIONCOMPONENT_H
