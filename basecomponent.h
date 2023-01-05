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
    BaseComponent(class Actor* InOwner);

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


protected:
    class Actor* GetOwner(BaseComponent* InChild);

//    void SetOwner(class Actor* )

private:
    Actor* mOwner {nullptr};
};

#endif // BASECOMPONENT_H
