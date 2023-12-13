#ifndef CPPTEST_COLLECTOROUTPUT_H
#define CPPTEST_COLLECTOROUTPUT_H

#include <list>
#include <string>
#include <vector>

#include "cpptest-output.h"
#include "cpptest-source.h"
#include "cpptest-time.h"

namespace Test {
/// \brief Collector output.
///
/// Base class for output handlers that need to report status when all
/// tests have executed.
///
class CollectorOutput : public Output {
   public:
	virtual void finished(int tests, const Time& time);
	virtual void suite_start(int tests, const std::string& name);
	virtual void suite_end(int tests, const std::string& name,
	                       const Time& time);
	virtual void test_start(const std::string& name);
	virtual void test_end(const std::string& name, bool ok,
	                      const Time& time);
	virtual void assertment(const Source& s);

   protected:
	struct OutputSuiteInfo;
	struct OutputTestInfo;
	struct OutputErrorTestInfo;

	typedef std::list<Source> Sources;

	struct TestInfo {
		std::string _name;
		Time _time;

		bool _success : 1;
		Sources _sources;

		explicit TestInfo(const std::string name);
	};

	typedef std::vector<TestInfo> Tests;

	struct SuiteInfo {
		std::string _name;
		int _errors;
		Tests _tests;
		Time _time;

		SuiteInfo(const std::string& name, int tests);
	};

	typedef std::list<SuiteInfo> Suites;

	Suites _suites;
	int _total_errors;
	int _total_tests;
	Time _total_time;

	CollectorOutput();

   private:
	SuiteInfo* _cur_suite;
	TestInfo* _cur_test;
};

}  // namespace Test

#endif  // #ifndef CPPTEST_COLLECTOROUTPUT_H
