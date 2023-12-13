#ifndef CPPTEST_SOURCE_H
#define CPPTEST_SOURCE_H

#include <string>

namespace Test {
class Suite;

/// \brief Assertment source information.
///
/// Contains information about an assertment point.
///
class Source {
	friend class Suite;

   public:
	Source();
	Source(const char* file, unsigned int line, const char* msg);

	const std::string& file() const;
	unsigned int line() const;
	const std::string& message() const;
	const std::string& suite() const;
	const std::string& test() const;

   private:
	unsigned int _line;
	std::string _file;
	std::string _msg;
	std::string _suite;
	std::string _test;
};

}  // namespace Test

#endif  // #ifndef CPPTEST_SOURCE_H
