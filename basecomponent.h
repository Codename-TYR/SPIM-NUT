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

    virtual void ComponentTick() = 0;

    virtual void InitializeComponentType() = 0;

    bool mEnableComponentTick {false};

protected:
    EComponentType ComponentType {EComponentType::ECT_None};


public:
    EComponentType GetComponentType() {return ComponentType;}


protected:
    class Actor* GetOwner(BaseComponent* InChild);

//    void SetOwner(class Actor* )

private:
    Actor* mOwner {nullptr};
};

#endif // BASECOMPONENT_H
