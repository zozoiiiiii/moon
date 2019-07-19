/************************************************************************/
/*
@author:   [junliang]
@time:     [7/19/2019]
@desc:     
*/
/************************************************************************/
#pragma once
#include "public/object/mn_object.h"


class DUILIB_API IWindow : public MN::BaseObject
{
public:
    virtual void OnCreate();
    virtual void OnDestroy();
    virtual bool create(const char* name, int x, int y, int width, int height)=0;
    virtual void show()=0;
    virtual void close()=0;
};
