#if (defined(__WIN32__) || defined(WIN32))
#include "winconfig.h"
#endif

#include "missing.h"
#include "utils.h"

namespace Test {
// Computes the procentage of correct tests.
//
int correct(int tests, int errors) {
	if ((errors == 0) || (tests == 0))
		return 100;

	return (tests - errors) * 100 / tests;
}

}  // namespace Test
