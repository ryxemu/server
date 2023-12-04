#ifndef __EQEMU_TESTS_STRING_UTIL_H
#define __EQEMU_TESTS_STRING_UTIL_H

#include "cppunit/cpptest.h"
#include "../common/strings.h"

class StringUtilTest : public Test::Suite {
	typedef void (StringUtilTest::*TestFunction)(void);

   public:
	StringUtilTest() {
		TEST_ADD(StringUtilTest::StringFormatTest);
		TEST_ADD(StringUtilTest::EscapeStringTest);
		TEST_ADD(StringUtilTest::EscapeStringMemoryTest);
	}

	~StringUtilTest() {
	}

   private:
	void StringFormatTest() {
		const char* fmt = "Test: %c %d %4.2f";
		char c = 'a';
		int i = 2014;
		float f = 3.1416;

		auto s = StringFormat(fmt, c, i, f);
		TEST_ASSERT_EQUALS(s.length(), 17);
		TEST_ASSERT(s.compare("Test: a 2014 3.14") == 0);
	}

	void EscapeStringTest() {
		std::string t;
		t.resize(10);
		t[0] = 'a';
		t[1] = 'b';
		t[2] = 'c';
		t[3] = '\x00';
		t[4] = '\n';
		t[5] = '\r';
		t[6] = '\\';
		t[7] = '\'';
		t[8] = '\"';
		t[9] = '\x1a';

		auto s = Strings::Escape(t);
		TEST_ASSERT(s.compare("abc\\x00\\n\\r\\\\\\'\\\"\\x1a") == 0);
	}

	void EscapeStringMemoryTest() {
		char t[10] = {0};
		t[0] = 'a';
		t[1] = 'b';
		t[2] = 'c';
		t[3] = '\x00';
		t[4] = '\n';
		t[5] = '\r';
		t[6] = '\\';
		t[7] = '\'';
		t[8] = '\"';
		t[9] = '\x1a';

		auto s = Strings::EscapePair(t, 10);
		TEST_ASSERT(s.compare("abc\\x00\\n\\r\\\\\\'\\\"\\x1a") == 0);
	}
};

#endif
