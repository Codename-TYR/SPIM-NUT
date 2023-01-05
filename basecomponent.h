#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

enum EComponentType
{
    ECT_None, ECT_CollisionComponent, ECT_BallComponent, ECT_MeshComponent, ECT_ScriptComponent, ECT_SoundComponent
};

class BaseComponent
{
public:
    BaseComponent();

    virtual void ComponentTick(float deltaTime) = 0;

    virtual void DrawComponent()=0;

    virtual void InitializeComponentType() = 0;

    bool mEnableComponentTick {false};

    void SetParent(class Actor* newParent);

    EComponentType ComponentType {EComponentType::ECT_None};
protected:

    class Actor* mParentActor{nullptr};

public:
    EComponentType GetComponentType() {return ComponentType;}

};

#endif // BASECOMPONENT_H
