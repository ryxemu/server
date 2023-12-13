#if (defined(__WIN32__) || defined(WIN32))
#include "winconfig.h"
#endif

#include "missing.h"

#ifdef HAVE_GETTICKCOUNT
#include <windows.h>
#endif

#ifndef __BORLANDC__
#include <cmath>
#else
#include <math.h>
#endif

#include <cassert>
#include <ctime>

namespace Test {
#ifndef HAVE_GETTIMEOFDAY

int gettimeofday(timeval* tv, void*) {
	assert(tv);

#ifdef HAVE_GETTICKCOUNT
	long now = GetTickCount();
	tv->tv_sec = now / 1000;
	tv->tv_usec = (now % 1000) * 1000;
#else
	tv->tv_sec = time(0);
	tv->tv_usec = 0;
#endif  // #ifdef HAVE_GETTICKCOUNT

	return 0;
}

#endif  // #ifndef HAVE_GETTIMEOFDAY

#ifndef HAVE_ROUND
double
round(double d) {
	return d > 0.0 ? floor(d + 0.5) : ceil(d - 0.5);
}
#endif

}  // namespace Test
