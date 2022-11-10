#ifndef NUTOBJECT_H
#define NUTOBJECT_H

#include <QVector3D>
#include "world.h"

class NUTObject
{
private:

public:
    NUTObject();
    virtual void renderInEditor()=0;
};

#endif // NUTOBJECT_H
