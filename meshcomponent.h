#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include "basecomponent.h"
#include "visualobject.h"

enum DrawMethod {LineLoop = GL_LINE_LOOP, Triangles = GL_TRIANGLES };

class MeshComponent : public BaseComponent, public VisualObject
{
public:
    MeshComponent(std::vector<Vertex> InVerteces);

    void init(GLint matrixUniform) override;
    void draw() override;
    void DrawComponent() override;

    void ComponentTick(float deltaTime) override {};
    void SetDrawMethod(DrawMethod method);
private:
    void InitializeComponentType() override {ComponentType = EComponentType::ECT_MeshComponent;};
    DrawMethod mDrawMethod{Triangles};

};

#endif // MESHCOMPONENT_H
