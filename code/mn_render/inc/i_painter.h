/************************************************************************/
/* 
@author:    junliang
@brief:     painter, used for 2d ui
        use one single interface to draw all 2d items, can control the drawcall.
@time:      2017-6-15
*/
/************************************************************************/
#pragma once

class IPainter : public MN::BaseObject
{
public:
    bool drawRectangle()=0;
    bool drawFont()=0;
    bool drawImage()=0;
};