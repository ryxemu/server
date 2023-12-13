#ifndef CPPTEST_HTMLOUTPUT_H
#define CPPTEST_HTMLOUTPUT_H

#include <iostream>
#include <string>

#include "cpptest-collectoroutput.h"

namespace Test {
/// \brief HTML output.
///
/// %Output handler that creates a HTML table with detailed information
/// about all tests.
///
class HtmlOutput : public CollectorOutput {
   public:
	void generate(std::ostream& os, bool incl_ok_tests = true,
	              const std::string& name = "");

   private:
	struct SuiteRow;
	struct TestRow;
	struct TestSuiteRow;
	struct TestResult;
	struct TestResultAll;
	struct SuiteTestResult;

	friend struct TestSuiteRow;
};

}  // namespace Test

#endif  // #ifndef CPPTEST_HTMLOUTPUT_H
