#ifndef CPPTEST_TIME_H
#define CPPTEST_TIME_H

#include <iostream>
#include <string>

namespace Test {
/// \brief %Time representation.
///
/// Encapsulates a time value with microsecond resolution. It is possible
/// to retrieve the current time, add and subtract time values, and output
/// the time to an output stream.
///
class Time {
   public:
	Time();
	Time(unsigned int sec, unsigned int usec);

	unsigned int seconds() const;
	unsigned int microseconds() const;

	static Time current();

	friend Time operator+(const Time& t1, const Time& t2);
	friend Time operator-(const Time& t1, const Time& t2);

	friend std::ostream& operator<<(std::ostream& os, const Time& t);

   private:
	unsigned int _sec;
	unsigned int _usec;
};

}  // namespace Test

#endif  // #ifndef CPPTEST_TIME_H
