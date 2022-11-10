# Husk å putte .dll fila i build mappa! :D

## Fysikk/Script interface
### Base Component
```
class BaseComponent
{
private:
    bool mEnableTick{false};
public:
    virtual void ComponentTick(float deltaTime, Actor* parentActor)=0;
};
```
### Fysikk Component
```
class PhysicsComponent : BaseComponent
{
public:
    void ComponentTick(float deltaTime, Actor* parentActor) override;
    
    QVector3D GetVelocity();
    
    void AddForce(QVector3D force);
    void AddForce(QVector3D direction, float multiplier);
    
private:
    float mMass;
    QVector3D mVelocity;
};
```
### Actor class
```
class Actor : VisualObject
{
private:
    QVector3D mPosition;
    QVector3D mRotation;
    std::vector<BaseComponent*> mComponents;
    void Tick(float deltaTime) {
        for (auto p : mComponents) {
            p->ComponentTick(deltaTime, this);
        }
    }
public:
    Actor();

    // POSITION
    void WorldTranslate(QVector3D offset);
    void LocalTranslate(QVector3D offset);
    void SetWorldLocation(QVector3D);
    QVector3D GetWorldLocation();

    // ROTATION
    void LocalRotation(QVector3D Rotator)
    {
        //mMatrix.rotate(Rotator.x(), {1,0,0});
        //mMatrix.rotate(Rotator.y(), {0,1,0});
        //mMatrix.rotate(Rotator.z(), {0,0,1});
    }
    QVector3D GetRotation();
    
};
```
