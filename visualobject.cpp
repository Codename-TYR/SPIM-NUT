// VisualObject.cpp
#include "visualobject.h"

VisualObject::VisualObject() {
    mRotation.setToIdentity();
    mScale.setToIdentity();
    mPosition.setToIdentity();
}


VisualObject::~VisualObject() {
   glDeleteVertexArrays( 1, &mVAO );
   glDeleteBuffers( 1, &mVBO );
}

void VisualObject::move(float x, float y, float z)
{
    mMatrix.translate(x, y, z);
}

void VisualObject::setVertices(std::vector<Vertex> vertices) {
    mVertices = vertices;
}

CrapVector3 VisualObject::Barycentric(CrapVector3 object, CrapVector3 P1, CrapVector3 P2, CrapVector3 P3)
{
    P1.setZ(0);
    P2.setZ(0);
    P3.setZ(0);

    CrapVector3 P12 = (P2-P1);
    CrapVector3 P13 = (P3-P1);

    CrapVector3 n = CrapVector3::crossProduct(P12, P13);
    float areal_123 = n.length();

    CrapVector3 baryc;

    // u
    CrapVector3 p = P2 - object;
    CrapVector3 q = P3 - object;
    n = CrapVector3::crossProduct(p,q);
    baryc.setX(n.z()/areal_123);

    // v
    p = P3 - object;
    q = P1 - object;
    n = CrapVector3::crossProduct(p,q);
    baryc.setY(n.z()/areal_123);

    // w
    p = P1 - object;
    q = P2 - object;
    n = CrapVector3::crossProduct(p,q);
    baryc.setZ(n.z()/areal_123);

    return baryc;

}

bool VisualObject::isOverlappingTriangle(CrapVector3 baryc, CrapVector3 P1, CrapVector3 P2, CrapVector3 P3)
{
    //auto baryc = Barycentric(P1, P2, P3);
    return baryc.x() >= 0.f && baryc.y() >= 0.f && baryc.z() >= 0.f;
}

float VisualObject::GetBarycentricHeight(CrapVector3 baryc, CrapVector3 P1, CrapVector3 P2, CrapVector3 P3)
{
    //auto baryc = Barycentric(P1, P2, P3);
    return P1.z() * baryc.x() + P2.z() * baryc.y() + P3.z() * baryc.z();
}

void VisualObject::setName(std::string name)
{
    mName = name;
}

std::string VisualObject::Name()
{
    return mName;
}

CrapVector3 VisualObject::getPosition()
{
    auto pos = mMatrix.column(3);
    return CrapVector3{pos.x(), pos.y(), pos.z()};
}

