#ifndef LIGHT_H
#define LIGHT_H

#include "crapvectors.h"
#include "visualobject.h"

///Simple Light class that has a small mesh and some light parameters
class Light : public VisualObject
{
public:
    ///Light class with mesh and light parameters
    Light();
    virtual void init(GLint matrixUniform) override;
    virtual void draw() override;

    CrapVector3 mOrbitPoint;

    GLfloat mAmbientStrenght{0.3f};
    CrapVector3 mAmbientColor{0.3f, 0.3f, 0.3f};  //Grey

    GLfloat mLightStrenght{0.7f};
    CrapVector3 mLightColor{0.9f, 0.9f, 0.9f};    //Yellow

    GLfloat mSpecularStrenght{0.2f};
    GLint mSpecularExponent{1};

    void setOrbitPoint(CrapVector3 pt);
    void orbit(float dt);
    void setVertices(std::vector<Vertex> in) override {mVertices = in;};
};

#endif // LIGHT_H
