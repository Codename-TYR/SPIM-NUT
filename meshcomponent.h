#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include "basecomponent.h"
#include "visualobject.h"

class MeshComponent : public BaseComponent, public VisualObject
{
public:
    MeshComponent(std::vector<Vertex> InVerteces);

    void init(GLint matrixUniform) override;
    void draw() override;

    void ComponentTick() override {};

private:
    void InitializeComponentType() override {ComponentType = EComponentType::ECT_MeshComponent;};


};

#endif // MESHCOMPONENT_H
