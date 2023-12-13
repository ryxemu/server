#ifndef __EQEMU_TESTS_SKILLS_UTILS_H
#define __EQEMU_TESTS_SKILLS_UTILS_H

#include "cppunit/cpptest.h"
#include "../common/skills.h"

class SkillsUtilsTest : public Test::Suite {
	typedef void (SkillsUtilsTest::*TestFunction)(void);

   public:
	SkillsUtilsTest() {
		TEST_ADD(SkillsUtilsTest::IsTradeskill);
		TEST_ADD(SkillsUtilsTest::IsSpecializedSkill);
	}

	~SkillsUtilsTest() {
	}

   private:
	void IsTradeskill() {
		TEST_ASSERT(EQ::skills::IsTradeskill(EQ::skills::SkillPottery));
		TEST_ASSERT(!EQ::skills::IsTradeskill(EQ::skills::SkillParry));
	}

	void IsSpecializedSkill() {
		TEST_ASSERT(EQ::skills::IsSpecializedSkill(EQ::skills::SkillSpecializeConjuration));
		TEST_ASSERT(!EQ::skills::IsSpecializedSkill(EQ::skills::SkillConjuration))
	}
};

#endif
