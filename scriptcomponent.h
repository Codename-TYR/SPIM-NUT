#ifndef SCRIPTCOMPONENT_H
#define SCRIPTCOMPONENT_H

#include "basecomponent.h"

class ScriptComponent : public BaseComponent
{
public:
    ScriptComponent();

    void ComponentTick() override {};

private:
    void InitializeComponentType() override {ComponentType = EComponentType::ECT_ScriptComponent;}
};

#endif // SCRIPTCOMPONENT_H
