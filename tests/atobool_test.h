#ifndef __EQEMU_TESTS_ATOBOOL_H
#define __EQEMU_TESTS_ATOBOOL_H

#include "cppunit/cpptest.h"
#include "../common/strings.h"

class atoboolTest : public Test::Suite {
	typedef void (atoboolTest::*TestFunction)(void);

   public:
	atoboolTest() {
		TEST_ADD(atoboolTest::TrueTest);
		TEST_ADD(atoboolTest::FalseTest);
		TEST_ADD(atoboolTest::YesTest);
		TEST_ADD(atoboolTest::NoTest);
		TEST_ADD(atoboolTest::OnTest);
		TEST_ADD(atoboolTest::OffTest);
		TEST_ADD(atoboolTest::EnableTest);
		TEST_ADD(atoboolTest::DisableTest);
		TEST_ADD(atoboolTest::EnabledTest);
		TEST_ADD(atoboolTest::DisabledTest);
		TEST_ADD(atoboolTest::YTest);
		TEST_ADD(atoboolTest::NTest);
		TEST_ADD(atoboolTest::nullptrTest);
	}

	~atoboolTest() {
	}

   private:
	void TrueTest() {
		TEST_ASSERT(atobool("true"));
	}

	void FalseTest() {
		TEST_ASSERT(!atobool("false"));
	}

	void YesTest() {
		TEST_ASSERT(atobool("yes"));
	}

	void NoTest() {
		TEST_ASSERT(!atobool("no"));
	}

	void OnTest() {
		TEST_ASSERT(atobool("on"));
	}

	void OffTest() {
		TEST_ASSERT(!atobool("off"));
	}

	void EnableTest() {
		TEST_ASSERT(atobool("enable"));
	}

	void DisableTest() {
		TEST_ASSERT(!atobool("disable"));
	}

	void EnabledTest() {
		TEST_ASSERT(atobool("enabled"));
	}

	void DisabledTest() {
		TEST_ASSERT(!atobool("disabled"));
	}

	void YTest() {
		TEST_ASSERT(atobool("y"));
	}

	void NTest() {
		TEST_ASSERT(!atobool("n"));
	}

	void nullptrTest() {
		TEST_ASSERT(!atobool(nullptr));
	}
};

#endif
