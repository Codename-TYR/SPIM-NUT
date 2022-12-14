#include "xyz.h"

XYZ::XYZ()
{
    mVertices.push_back(Vertex{0,0,0,1,0,0});   // X-Axis, red
    mVertices.push_back(Vertex{1,0,0,1,0,0});

    mVertices.push_back(Vertex{0,0,0,0,1,0});   // Y-Axis, green
    mVertices.push_back(Vertex{0,1,0,0,1,0});

    mVertices.push_back(Vertex{0,0,0,0,0,1});   // z-Axis, blue
    mVertices.push_back(Vertex{0,0,1,0,0,1});
    mMatrix.setToIdentity();
}

XYZ::~XYZ() {}

void XYZ::init(GLint matrixUniform)
{
    mMatrixUniform = matrixUniform;
    initializeOpenGLFunctions();

    glGenVertexArrays( 1, &mVAO );
    glBindVertexArray( mVAO );

    glGenBuffers( 1, &mVBO );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO );

    glBufferData(
                GL_ARRAY_BUFFER,                          //what buffer type
                mVertices.size() * sizeof( Vertex ),      //how big buffer do we need
                mVertices.data(),                         //the actual vertices
                GL_STATIC_DRAW                            //should the buffer be updated on the GPU
            );

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(
                0,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Vertex),
                reinterpret_cast<GLvoid*>(0)
            );                              // array buffer offset
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
                1,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Vertex),
                reinterpret_cast<GLvoid*>((3 * sizeof(GLfloat)))
                );
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); //Releases binds

}

void XYZ::draw()
{
   glBindVertexArray( mVAO );
   glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
   glDrawArrays(GL_LINES, 0, mVertices.size());
}

