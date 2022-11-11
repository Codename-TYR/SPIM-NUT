#ifndef CAMERA_H
#define CAMERA_H

#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include "crapvectors.h"

#include "visualobject.h"

class Camera : public QOpenGLFunctions_4_1_Core
{
private:
    GLint  mPmatrixUniform;
    GLint  mVmatrixUniform;
    CrapVector3 mEye;


    VisualObject* mTarget{nullptr};
    float mDistanceToTarget{5.f};
    float mZoomSensitivity = 0.1f;
    float mMovementSensitivity = 0.5f;
    bool mCameraIsBusy{false};
    bool mAllowDirectionChange{false};
    bool mStaticPosition{false};
    CrapVector3 oldTargetPos;
    float pitch{0.f}, yaw{0.f};
public:

    QMatrix4x4 mPmatrix{};
     QMatrix4x4 mVmatrix{};
    CrapVector3 GetPosition();
    Camera();
    ~Camera();
    void init(GLint pMatrixUniform, GLint vMatrixUniform);
    void perspective(float degrees, double aspect, double nearplane, double farplane);
    void lookAt(const CrapVector3 &at);
    void lookAt(const CrapVector3& eye, const CrapVector3& at, const CrapVector3& up);
    void rotateAround(int degrees, const CrapVector3 &around);
    void rotateAround(float magnitude, const CrapVector3 direction);
    void followMouseMovements(float x, float y);
    void update();
    void SetTarget(VisualObject* target);
    void SetStatic(bool isStatic = true);
    void Tick(float deltaTime);
    void Zoom(float diff);
    void setAllowedToFollow(bool status);

    CrapVector3 Forward();
    CrapVector3 Right();
//    void rotate(){mVmatrix.rotate(1, {0, 0, 1});}

    CrapVector3 Up();
    void SetPosition(const CrapVector3 &newPos);
    void update(GLint pMat, GLint vMat);
    void Move(CrapVector3 direction, float speed);
    void firstPersonMouseMove(float x, float y);
};


#endif // CAMERA_H
