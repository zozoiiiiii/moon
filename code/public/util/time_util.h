/************************************************************************/
/*
@author:  junliang
@brief:   time
http://www.cplusplus.com/reference/ctime

@time:    20130510
*/
/************************************************************************/
#pragma once

#include "public/object/mn_type.h"
#include <string>

class TimeUtil
{
public:
    //get micro seconds from epoch
    static sint64 TimeStamp();

    //string time format: 2014-04-08 11:04:48.21348
    static std::string StrTimeStamp();
};
