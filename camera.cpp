#include "camera.h"
#include <iostream>
CrapVector3 Camera::GetPosition()
{
    return mEye;
}

Camera::Camera() : mEye{3, -10, 8}
{

    mVmatrix.setToIdentity();
}

Camera::~Camera()
{

}

void Camera::Move(CrapVector3 direction, float speed)
{
    mEye += (-direction * speed);
    mVmatrix.translate(direction * speed);
}

void Camera::init(GLint pMatrixUniform, GLint vMatrixUniform)
{

    mVmatrix.setToIdentity();

    mPmatrixUniform = pMatrixUniform;
    mVmatrixUniform = vMatrixUniform;
    lookAt({0,0,0});
}

void Camera::perspective(float degrees, double aspect, double nearplane, double farplane)
{

    mPmatrix.perspective(degrees, aspect, nearplane, farplane);
    //mPmatrix.frustum(-1, 1, -1, 1, 1, 100);
}

void Camera::lookAt(const CrapVector3 &eye, const CrapVector3 &at, const CrapVector3 &up)
{
    mVmatrix.setToIdentity();
    mVmatrix.lookAt(eye, at, up);
}

void Camera::rotateAround(int degrees, const CrapVector3 &around)
{
    //    for (int i = 0; i < degrees; i++) {
    //        mEye.setY(mEye.y()+.01f);
    //        mVmatrix.translate(0, 0.01, 0);
    //        lookAt(around);
    //    }

    QMatrix4x4 rotation;
    rotation.setToIdentity();

    rotation.translate(around);
    rotation.rotate(degrees, {0, 0, 1});
    rotation.translate(-around);

    mEye = rotation * mEye;

    mVmatrix.setToIdentity();

    mVmatrix.lookAt(mEye, around, CrapVector3{0, 0, 1});

}

void Camera::rotateAround(float magnitude, const CrapVector3 direction)
{
    if (mTarget == nullptr) return;

    QMatrix4x4 rotation;

    rotation.setToIdentity();

    CrapVector3 around = mTarget->getPosition();

    rotation.translate(around);
    rotation.rotate(magnitude, direction);
    rotation.translate(-around);

    mEye = rotation * mEye;

    mVmatrix.setToIdentity();

    mVmatrix.lookAt(mEye, around, CrapVector3{0, 0, 1});
}

void Camera::firstPersonMouseMove(float x, float y)
{
    mVmatrix.translate(mEye);
    mVmatrix.rotate(-x * mMovementSensitivity,0,0,1);
    mVmatrix.rotate(y * mMovementSensitivity, {Right()});
    mVmatrix.translate(-mEye);

}

void Camera::followMouseMovements(float x, float y)
{

    QMatrix4x4 rotation;

    rotation.setToIdentity();
    CrapVector3 around;
    if (mTarget == nullptr) {
        around = {0, 0, 0};
    } else {
        around = mTarget->getPosition();
    }

    CrapVector3 oldPosition = mEye;
    CrapVector3 oldRight = Right();

    x *= mMovementSensitivity;
    y *= mMovementSensitivity;

    rotation.translate(around);
    rotation.rotate(y, Right());
    rotation.rotate(x * Up().z(), Up());
    rotation.translate(-around);

    mEye = rotation.map(mEye);

    if (CrapVector3::dotProduct(Right(), oldRight) < 0)
        mEye = oldPosition;
    //std::cout << "X: " << Right().x() << "y: " << Right().y() << "Z: " << Right().z() << std::endl;

    mVmatrix.setToIdentity();

    mVmatrix.lookAt(mEye, around, CrapVector3{0, 0, 1});
}

void Camera::lookAt(const CrapVector3 &at)
{
    mVmatrix.setToIdentity();
    mVmatrix.lookAt(mEye, at, CrapVector3{0, 0, 1});
}

void Camera::update()
{
    initializeOpenGLFunctions();
    glUniformMatrix4fv(mPmatrixUniform, 1, GL_FALSE, mPmatrix.constData());
    glUniformMatrix4fv(mVmatrixUniform, 1, GL_FALSE, mVmatrix.constData());
}

void Camera::update(GLint pMat, GLint vMat)
{
    initializeOpenGLFunctions();
    glUniformMatrix4fv(pMat, 1, GL_FALSE, mPmatrix.constData());
    glUniformMatrix4fv(vMat, 1, GL_FALSE, mVmatrix.constData());
}

void Camera::SetTarget(VisualObject *target)
{
    mTarget = target;
}

void Camera::SetStatic(bool isStatic)
{
    mStaticPosition = isStatic;
}

void Camera::SetPosition(const CrapVector3& newPos) {
    mEye = newPos;
}

void Camera::Tick(float deltaTime)
{

}

void Camera::Zoom(float diff)
{
    diff = std::clamp(diff, -10.f, 10.f) * mZoomSensitivity;
    mDistanceToTarget = std::clamp(mDistanceToTarget - diff, 5.f, 60.f);
}

void Camera::setAllowedToFollow(bool status)
{
    mAllowDirectionChange = status;
}

CrapVector3 Camera::Forward()
{

    CrapVector3 vec = mVmatrix.row(2).toVector3D();


    //std::cout << "X: " << out.x() << "y: " << out.y() << "Z: " << out.z() << std::endl;
    return vec;
}

CrapVector3 Camera::Right()
{
    CrapVector3 vec = mVmatrix.row(0).toVector3D();


    //std::cout << "X: " << out.x() << "y: " << out.y() << "Z: " << out.z() << std::endl;
    return -vec;
}

CrapVector3 Camera::Up()
{
    CrapVector3 out = CrapVector3::crossProduct(Right(), Forward());

    out.normalize();
    //std::cout << "X: " << out.x() << "y: " << out.y() << "Z: " << out.z() << std::endl;
    return out;
}

