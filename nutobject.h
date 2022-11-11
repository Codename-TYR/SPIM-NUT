#ifndef NUTOBJECT_H
#define NUTOBJECT_H

#include "crapvectors.h"
#include "world.h"

class NUTObject
{
private:

public:
    NUTObject();
    virtual void renderInEditor()=0;
};

#endif // NUTOBJECT_H
