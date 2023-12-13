#ifndef CPPTEST_TEXTOUTPUT_H
#define CPPTEST_TEXTOUTPUT_H

#include <iostream>
#include <list>

#include "cpptest-source.h"
#include "cpptest-output.h"

namespace Test {
/// \brief Text output handler that outputs to the a stream.
///
/// %Test suite output handler that writes its information as text to a
/// a stream. It it possible to select between two different operational
/// modes that controls the detail level, see Mode.
///
class TextOutput : public Output {
   public:
	/// Output mode.
	///
	enum Mode {
		/// Terse output mode, which only shows the number of correct tests.
		///
		Terse,

		/// Verbose output mode, which also shows extended assert
		/// information for each test that failed.
		///
		Verbose
	};

	TextOutput(Mode mode, std::ostream& stream = std::cout);

	virtual void finished(int tests, const Time& time);
	virtual void suite_start(int tests, const std::string& name);
	virtual void suite_end(int tests, const std::string& name,
	                       const Time& time);
	virtual void test_end(const std::string& name, bool ok,
	                      const Time& time);
	virtual void assertment(const Source& s);

   private:
	typedef std::list<Source> ErrorList;

	Mode _mode;
	std::ostream& _stream;
	ErrorList _suite_error_list;
	std::string _suite_name;
	int _suite_errors;
	int _suite_tests;
	int _suite_total_tests;
	int _total_errors;
};

}  // namespace Test

#endif  // #ifndef CPPTEST_TEXTOUTPUT_H
