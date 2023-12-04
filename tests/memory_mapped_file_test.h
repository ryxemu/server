#ifndef __EQEMU_TESTS_MEMORY_MAPPED_FILE_H
#define __EQEMU_TESTS_MEMORY_MAPPED_FILE_H

#include "cppunit/cpptest.h"
#include "../common/memory_mapped_file.h"

class MemoryMappedFileTest : public Test::Suite {
	typedef void(MemoryMappedFileTest::*TestFunction)(void);
public:
	MemoryMappedFileTest() {
		TEST_ADD(MemoryMappedFileTest::LoadAndZeroMMF)
		TEST_ADD(MemoryMappedFileTest::LoadExistingMMF)
	}

	~MemoryMappedFileTest() {
	}

	private:
	void LoadAndZeroMMF() {
		EQ::MemoryMappedFile mmf("testfile.txt", 512);
		mmf.ZeroFile();
		TEST_ASSERT(mmf.Size() == 512);

		unsigned char *data = reinterpret_cast<unsigned char*>(mmf.Get());
		TEST_ASSERT(data != nullptr);

		*reinterpret_cast<uint32*>(data) = 562;
	}

	void LoadExistingMMF() {
		EQ::MemoryMappedFile mmf("testfile.txt");
		TEST_ASSERT(mmf.Size() == 512);

		unsigned char *data = reinterpret_cast<unsigned char*>(mmf.Get());
		TEST_ASSERT(data != nullptr);

		uint32 val = *reinterpret_cast<uint32*>(data);
		TEST_ASSERT(val == 562);
	}
};

#endif
