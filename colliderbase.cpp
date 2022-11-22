#include "colliderbase.h"



ColliderBase::ColliderBase()
{
    myID = amountOfColliders;
    amountOfColliders++;
}

void ColliderBase::ChangeColor(CurrentColor clr)
{
    QVector3D newColor;
    switch (clr)
    {
    case white:
        newColor = {1,1,1};
        break;
    case red:
        newColor = {1,0,0};
        break;
    default:
        break;
    }

    for (int i = 0; i < mVertices.size(); i++) {
        mVertices[i].setColor(newColor);
    }
    init(0);
    mCurrentColor = clr;
}

void ColliderBase::SetColorToRedThisTick()
{
    mColorSetToRedThisTick = true;
}

void ColliderBase::init(GLint matrixUniform)
{
    ///
    mMatrixUniform = matrixUniform;
    initializeOpenGLFunctions();

    //Vertex Array Object - VAO
    glGenVertexArrays( 1, &mVAO );
    glBindVertexArray( mVAO );

    //Vertex Buffer Object to hold vertices - VBO
    glGenBuffers( 1, &mVBO );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO );

    glBufferData(
                GL_ARRAY_BUFFER,
                mVertices.size()*sizeof(Vertex),
                mVertices.data(),
                GL_STATIC_DRAW
                );

    // 1rst attribute buffer : vertices
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(
                0,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Vertex),
                reinterpret_cast<const void*>(0)
                );
    glEnableVertexAttribArray(0);

    // 2nd attribute buffer : colors
    glVertexAttribPointer(
                1,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Vertex),
                reinterpret_cast<const void*>(3 * sizeof(GLfloat))
                );
    glEnableVertexAttribArray(1);

    //enable the matrixUniform
    // mMatrixUniform = glGetUniformLocation( matrixUniform, "matrix" );
    glGenBuffers(1, &mIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size()*sizeof(GLuint), mIndices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void ColliderBase::draw()
{
    if (mColorSetToRedThisTick) {
        if (!mWasRedLastTick) {
            ChangeColor(red);
        }
        mWasRedLastTick = true;
    } else {
        if (mWasRedLastTick) {
            ChangeColor(white);
        }
        mWasRedLastTick = false;
    }
    glUniformMatrix4fv(mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    initializeOpenGLFunctions();
    glBindVertexArray( mVAO );
    glDrawElements(GL_LINE_LOOP, mIndices.size(), GL_UNSIGNED_INT, reinterpret_cast<const void*>(0));//mVertices.size());
    mColorSetToRedThisTick = false;
}
