#ifndef OCTAHEDRONBALL_H
#define OCTAHEDRONBALL_H
#include "crapvectors.h"
#include <vector>
#include <vertex.h>
#include <iostream>
#include <sstream>

class OctahedronBall
{
private:
    static void lagTriangel(std::vector<Vertex>& mVertices, const CrapVector3& v1, const CrapVector3& v2, const CrapVector3& v3);
    static void subDivide(std::vector<Vertex>& mVertices, const CrapVector3& a, const CrapVector3& b, const CrapVector3& c, int n);
public:
    static std::vector<Vertex> oktaederUnitBall(int n, const CrapVector3& color, float scale=1);
    static std::vector<Vertex> oktaederUnitBall(int n);
    static inline bool mUsingCustomColor{false};
    static inline float mScale{1};
    static inline CrapVector3 mColor{0, 0, 0};
    OctahedronBall();
    ~OctahedronBall();
};

#endif // OCTAHEDRONBALL_H
