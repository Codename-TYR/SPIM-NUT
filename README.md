# Fysikk og JavaScript
## Fysikk/Script interface
### Base Component
```cpp
class BaseComponent
{
private:
    bool mEnableTick{false};
    QVector3D mLocalOffset;
public:
    virtual void ComponentTick(float deltaTime)=0;
};
```
### Fysikk Component
```cpp
class PhysicsComponent : BaseComponent
{
public:
    void ComponentTick(float deltaTime) override;
    
    QVector3D GetVelocity();
    
    void AddForce(QVector3D force);
    void AddForce(QVector3D direction, float multiplier);
    
private:
    float mMass;
    QVector3D mVelocity;
};
```
### Actor class
```cpp
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

# Lyd
## Lyd-Komponent interface
```cpp
class Sound {
public:
    Sound(std::string filePath);
    void Play();
    void Pause();
    void Stop();
};

class SoundComponent : BaseComponent
{
public:
    void ComponentTick(float deltaTime) override;
    
    // Den første viser implementasjon, men dette skal i en cpp fil, pause og stop skal være relativt like
    void Play(std::string sound) {
        if (mSounds[sound] == nullptr) return;
        mSounds[sound]->Play();
    }
    void Pause(std::string sound);
    void Stop(std::string sound);
    
    void Load(std::string filePath, std::string name) {
        Sound* sound = new Sound(filePath);
        mSounds[name] = sound;
    }
    
private:
    std::map<std::string, Sound*> mSounds;
};
```
