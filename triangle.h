#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vertex.h"

class Triangle
{
public:
    Triangle(const Vertex &v1, const Vertex &v2, const Vertex &v3);
    ~Triangle();
    const Vertex* verts[3];
    void SetVertices(const Vertex& v1, const Vertex& v2, const Vertex& v3);
};

#endif // TRIANGLE_H
