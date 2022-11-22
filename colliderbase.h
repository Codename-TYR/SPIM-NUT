#ifndef COLLIDERBASE_H
#define COLLIDERBASE_H
#include "visualobject.h"

class ColliderBase : public VisualObject
{
protected:
    enum ColliderType {Plane, Sphere, Box, Triangle};
    enum CurrentColor { white, red };
    std::vector<GLuint> mIndices;
    GLuint mIBO{0};
    static inline unsigned int amountOfColliders{0};
    unsigned int myID;
    ColliderBase();
    bool mColorSetToRedThisTick{false};
    bool mWasRedLastTick{false};
    CurrentColor mCurrentColor{white};
public:
    void SetColorToRedThisTick();
    virtual QVector3D GetCollisionDirectionFromTarget(ColliderBase* source)=0;
    ColliderType mColliderType;
    virtual void init(GLint matrixUniform) override;
    virtual void draw() override;
    void ChangeColor(CurrentColor clr);
};

#endif // COLLIDERBASE_H
