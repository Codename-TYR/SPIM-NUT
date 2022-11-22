#include "triangle.h"
#include "vertex.h"

Triangle::Triangle(const Vertex &v1, const Vertex &v2, const Vertex &v3)
{
    verts[0] = &v1;
    verts[1] = &v2;
    verts[2] = &v3;
}

Triangle::~Triangle()
{
}

void Triangle::SetVertices(const Vertex &v1, const Vertex &v2, const Vertex &v3)
{
    verts[0] = &v1;
    verts[1] = &v2;
    verts[2] = &v3;
}

