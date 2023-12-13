#include "cpptest-source.h"

using namespace std;

namespace Test {
/// Constructs an invalid source object, which filename and message are
/// empty strings and the line equals zero.
///
Source::Source()
    : _line(0) {}

/// Constructs a source object.
///
/// \param file Name of the file containing the failing function.
/// \param line Line where the function starts.
/// \param msg  Expression (or message) that caused the failure.
///
Source::Source(const char* file, unsigned int line, const char* msg)
    : _line(line),
      _file(file ? file : ""),
      _msg(msg ? msg : "") {}

/// \return Name of the file containing the failing function.
///
const string&
Source::file() const {
	return _file;
}

/// \return Line where the function starts.
///
unsigned int
Source::line() const {
	return _line;
}

/// \return Descriptive message.
///
const string&
Source::message() const {
	return _msg;
}

/// \return Name of the suite, which the test belongs to.
///
const string&
Source::suite() const {
	return _suite;
}

/// \return Name of failing test.
///
const string&
Source::test() const {
	return _test;
}

}  // namespace Test
