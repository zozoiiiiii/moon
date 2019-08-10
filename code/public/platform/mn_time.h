/************************************************************************/
/*
@author:  junliang
@time:    20190810
@brief:   time
	sint64 nTimeStamp = MNTime::TimeStamp();
	std::string strTimeStamp = MNTime::StrTimeStamp();
*/
/************************************************************************/
#pragma once

#include "mn_platform.h"

#ifdef _MN_PLATFORM_WIN32_
#include "implement/win_time.h"
#endif

#ifdef _MN_PLATFORM_ANDROID_
#endif

#ifdef _MN_PLATFORM_UTIL_APPLE_
#endif