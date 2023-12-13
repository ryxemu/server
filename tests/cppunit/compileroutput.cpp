#include <cstring>
#include <sstream>

#include "cpptest-compileroutput.h"
#include "cpptest-source.h"

using namespace std;

namespace Test {
namespace {
// Checks for output format modifiers.
//
bool check_format(const string& format,
                  string::size_type& pos,
                  const string& mod,
                  int& mod_cnt) {
	if (format.compare(pos, mod.size(), mod) == 0) {
		if (++mod_cnt > 1)
			throw Test::CompilerOutput::InvalidFormat(format);
		pos += mod.size();
		return true;
	}
	return false;
}

}  // anonymous namespace

/// Constructs a compiler output handler.
///
/// \param format Pre-defined compiler output format.
/// \param stream Stream to output to.
///
CompilerOutput::CompilerOutput(Format format, ostream& stream)
    : Output(),
      _stream(stream) {
	static const char* table[] =
	    {
	        "%file:%line: %text",                // Generic
	        "Error cpptest %file %line: %text",  // BCC
	        "%file:%line: %text",                // GCC
	        "%file(%line) : %text"               // MSVC
	    };

	_format = table[format];
}

/// Constructs a compiler output handler.
///
/// \param format %Output format to use.
/// \param stream Stream to output to.
///
/// \exception InvalidFormat Invalid format specified.
///
CompilerOutput::CompilerOutput(const string& format, ostream& stream)
    : Output(),
      _format(format),
      _stream(stream) {
	int expr(0), file(0), line(0);

	for (string::size_type pos = 0;
	     (pos = _format.find_first_of('%', pos)) != string::npos;) {
		++pos;
		if (check_format(_format, pos, "expr", expr))
			;
		else if (check_format(_format, pos, "file", file))
			;
		else if (check_format(_format, pos, "line", line))
			;
		else
			throw InvalidFormat(format);
	}

	if (!expr && !file && !line)
		throw InvalidFormat(format);
}

void CompilerOutput::assertment(const Source& s) {
	string fmt(_format);
	string::size_type pos;

	fmt.reserve(fmt.size() + 128);

	if ((pos = fmt.find("%file")) != string::npos)
		fmt.replace(pos, 5, s.file());

	if ((pos = fmt.find("%text")) != string::npos)
		fmt.replace(pos, 5, s.message());

	if ((pos = fmt.find("%line")) != string::npos) {
		ostringstream ss;
		ss << s.line();
		fmt.replace(pos, 5, ss.str());
	}

	_stream << fmt << endl;
}

}  // namespace Test
