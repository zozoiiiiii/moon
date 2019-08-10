/************************************************************************/
/*
@author:  junliang
@time:    20190810
@brief:   time
*/
/************************************************************************/
#pragma once

#include "../mn_platform.h"
#include <windows.h>
#include <time.h>



class MNTime
{
public:
	//get micro seconds from epoch
	static sint64 TimeStamp()
	{
		struct timeval tv;
		gettimeofday(&tv, NULL);
		return tv.tv_sec * 1000 * 1000 + tv.tv_usec;
	}

	//string time format: 2014-04-08 11:04:48.21348
	static std::string StrTimeStamp()
	{
		char buf[200] = { 0 };
		timeval tv;
		gettimeofday(&tv, NULL);
		tm* pt = NULL;
		pt = _localtime32(&tv.tv_sec);

		sprintf(buf, "%4d-%02d-%02d %02d:%02d:%02d.%06d",
			pt->tm_year + 1900, pt->tm_mon + 1, pt->tm_mday,
			pt->tm_hour, pt->tm_min, pt->tm_sec,
			int(tv.tv_usec *0.001));
		return buf;
	}
private:
	struct timezone
	{
		int tz_minuteswest;
		int tz_dsttime;
	};
	static int gettimeofday(struct timeval *tv, struct timezone*)
	{
		FILETIME ft;
		sint64 tmpres = 0;
		memset(&ft, 0, sizeof(ft));
		GetSystemTimeAsFileTime(&ft);

		tmpres = ft.dwHighDateTime;
		tmpres <<= 32;
		tmpres |= ft.dwLowDateTime;

		/*converting file time to unix epoch*/
		tmpres /= 10;  /*convert into microseconds*/

#define DELTA_EPOCH_IN_MICROSECS 11644473600000000;
		tmpres -= DELTA_EPOCH_IN_MICROSECS;
		tv->tv_sec = (__int32)(tmpres*0.000001);
		tv->tv_usec = (long)(tmpres % 1000000);


		return 0;
	}
};

