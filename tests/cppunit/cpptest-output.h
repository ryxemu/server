#ifndef CPPTEST_OUTPUT_H
#define CPPTEST_OUTPUT_H

#include <string>

#ifdef _MSC_VER
#define CPPTEST_UNUSED(x)
#else
#define CPPTEST_UNUSED(x) (void)x
#endif

namespace Test {
class Source;
class Time;

/// \brief %Test suite output handler.
///
/// Abstract base class for all suite output handlers. Derive from this
/// class to create real output handlers that creates arbitrary complex
/// output handlers.
///
/// All parts of testing is reported (test start/stop, suite start/stop,
/// individual test start/stop, and assertments), thus giving maximum
/// flexibility for derived classes.
///
class Output {
   public:
	/// Empty destructor.
	///
	virtual ~Output() {}

	/// Called when testing is started.
	///
	/// \param tests Total number of tests in all suites.
	///
	virtual void initialize(int tests) {
		CPPTEST_UNUSED(tests);
	}

	/// Called when testing is finished.
	///
	/// \param tests Total number of tests in all suites.
	/// \param time  Total elapsed time for all tests.
	///
	virtual void finished(int tests, const Time& time) {
		CPPTEST_UNUSED(tests);
		CPPTEST_UNUSED(time);
	}

	/// Called when a suite is entered.
	///
	/// \param tests Number of tests in this suite.
	/// \param name  Name of the suite.
	///
	virtual void suite_start(int tests, const std::string& name) {
		CPPTEST_UNUSED(tests);
		CPPTEST_UNUSED(name);
	}

	/// Called when a suite is finished.
	///
	/// \param tests Number of tests in this suite.
	/// \param name  Name of the suite.
	/// \param time  Total elapsed time for all tests in this suite.
	///
	virtual void suite_end(int tests, const std::string& name,
	                       const Time& time) {
		CPPTEST_UNUSED(tests);
		CPPTEST_UNUSED(name);
		CPPTEST_UNUSED(time);
	}

	/// Called when a tests is executed.
	///
	/// \param name Name of the test function.
	///
	virtual void test_start(const std::string& name) {
		CPPTEST_UNUSED(name);
	}

	/// Called when a test if finished, regardless if an assertment was
	/// issued.
	///
	/// \param name Name of the test function.
	/// \param ok   True if the test was successful; false otherwise.
	/// \param time  Execution time.
	///
	virtual void test_end(const std::string& name, bool ok,
	                      const Time& time) {
		CPPTEST_UNUSED(name);
		CPPTEST_UNUSED(ok);
		CPPTEST_UNUSED(time);
	}

	/// Called when an assertment is issued.
	///
	/// \param s Assert point information.
	///
	virtual void assertment(const Source& s) {
		CPPTEST_UNUSED(s);
	}

   protected:
	/// Empty constructor.
	///
	Output() {}

   private:
	Output(const Output&);
	Output& operator=(const Output&);
};

}  // namespace Test

#endif  // #ifndef CPPTEST_OUTPUT_H
