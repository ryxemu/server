#ifndef CPPTEST_COMPILEROUTPUT_H
#define CPPTEST_COMPILEROUTPUT_H

#include <iostream>
#include <stdexcept>

#include "cpptest-output.h"

namespace Test {
/// \brief Compiler-like output handler.
///
/// %Test suite output handler that only outputs failures in compiler
/// warning/error format. This way, you can use your IDE to browse between
/// failures.
///
/// The output format is configurable to be able to emulate different
/// compiler outputs. The following modifiers exist:
/// - \e %file Outputs the file containing the test function.
/// - \e %line Line number for the the test function.
/// - \e %text Expression (or message) that caused the assertment.
/// Note that each modifier can only be specified once.
///
class CompilerOutput : public Output {
   public:
	/// \brief Compiler output exception.
	///
	/// Indicates that an invalid message format was given when creating
	/// a compiler output. The failing format may be retrieved using the
	/// what() method.
	///
	class InvalidFormat : public std::logic_error {
	   public:
		InvalidFormat(const std::string& what)
		    : std::logic_error(what) {}
	};

	/// Pre-defined compiler output formats.
	///
	enum Format {
		/// Generic compiler format, which equals:
		/// <tt>%%file:%%line: %%text</tt>
		///
		Generic,

		/// <a href="http://www.borland.com/products/downloads/download_cbuilder.html">
		/// Borland C++ Compiler</a> (BCC) format, which equals:
		/// <tt>Error cpptest %%file %%line: %%text</tt>.
		///
		BCC,

		/// <a href="http://gcc.gnu.org">GNU Compiler Collection</a>
		/// (GCC) format, which equals:
		/// <tt>%%file:%%line: %%text</tt>
		///
		GCC,

		/// <a href="http://www.microsoft.com">Microsoft Visual C++</a>
		/// (MSVC) format, which equals:
		/// <tt>%%file(%%line) : %%text</tt>
		///
		MSVC
	};

	explicit CompilerOutput(Format format = Generic,
	                        std::ostream& stream = std::cout);

	explicit CompilerOutput(const std::string& format,
	                        std::ostream& stream = std::cout);

	virtual void assertment(const Source& s);

   private:
	std::string _format;
	std::ostream& _stream;
};

}  // namespace Test

#endif  // #ifndef CPPTEST_COMPILEROUTPUT_H
