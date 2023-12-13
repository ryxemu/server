#ifndef CPPTEST_MISSING_H
#define CPPTEST_MISSING_H

#if (defined(__WIN32__) || defined(WIN32))
#include "winconfig.h"
#endif

namespace Test {
#ifndef HAVE_GETTIMEOFDAY

struct timeval {
	long tv_sec;
	long tv_usec;
};

extern int gettimeofday(timeval* tv, void*);

#endif  // #ifndef HAVE_GETTIMEOFDAY

#ifndef HAVE_ROUND
extern double round(double d);
#endif

}  // namespace Test

#endif  // #ifndef CPPTEST_MISSING_H
