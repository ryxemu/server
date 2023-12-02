#include "eqemu_exception.h"

namespace EQ {
Exception::Exception(const char* name, const std::string& description, const char* file, long line)
    : line_(line),
      file_(file),
      desc_(description),
      name_(name) {
}

Exception::Exception(const Exception& e)
    : line_(e.line_),
      file_(e.file_),
      desc_(e.desc_),
      name_(e.name_) {
}

#ifdef EQEMU_RVALUE_MOVE
Exception::Exception(const Exception&& e)
    : line_(e.line_),
      file_(e.file_),
      desc_(e.desc_),
      name_(e.name_) {
}
#endif

void Exception::operator=(const Exception& e) {
	line_ = e.line_;
	file_ = e.file_;
	desc_ = e.desc_;
	name_ = e.name_;
}

const std::string& Exception::full_description() const {
	if (full_desc_.empty()) {
		std::stringstream ss;
		ss << "EQEmu Exception (" << name_ << ") in " << file_;
		ss << " at line (" << line_ << "): " << desc_;
		full_desc_ = ss.str();
	}
	return full_desc_;
}
}  // namespace EQ
