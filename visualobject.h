#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include <string>
#include "vertex.h"

class VisualObject : public QOpenGLFunctions_4_1_Core {
public:
    VisualObject();
    ~VisualObject();
    virtual void init(GLint matrixUniform)=0;
    virtual void draw()=0;
    virtual void Tick(float deltaTime){};
    virtual void move(float x, float y, float z);
    virtual void move(float dt) { };
    virtual void setVertices(std::vector<Vertex> vertices);
    virtual CrapVector3 getPosition();
    void setName(std::string name);
    std::string Name();
    bool nameContains(std::string test){return mName.compare(test) == 1;};
    QMatrix4x4 mMatrix;
    CrapVector3 Barycentric(CrapVector3 object, CrapVector3 P1, CrapVector3 P2, CrapVector3 P3);
    bool isOverlappingTriangle(CrapVector3 baryc, CrapVector3 P1, CrapVector3 P2, CrapVector3 P3);
    float GetBarycentricHeight(CrapVector3 baryc, CrapVector3 P1, CrapVector3 P2, CrapVector3 P3);
protected:
    friend class InteractiveObject;
    std::vector<Vertex> mVertices;
    GLuint mVAO{0};
    GLuint mVBO{0};
    GLint mMatrixUniform{0};

    QMatrix4x4 mRotation;
    QMatrix4x4 mPosition;
    QMatrix4x4 mScale;
    CrapVector3 mVelocity{.1f, 0.f, 0.f};
    std::string mName;
};
#endif // VISUALOBJECT_H
