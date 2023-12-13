#include <iostream>
#include <fstream>
#include <memory>
#include "memory_mapped_file_test.h"
#include "ipc_mutex_test.h"
#include "fixed_memory_test.h"
#include "fixed_memory_variable_test.h"
#include "atobool_test.h"
#include "hextoi_32_64_test.h"
#include "string_util_test.h"
#include "data_verification_test.h"
#include "skills_util_test.h"
#include "../common/config.h"

const Config *Config;

int main() {
	auto ConfigLoadResult = Config::LoadConfig();
	Config = Config::get();
	std::cout << "Tests starting..." << std::endl;

	try {
		std::ofstream outfile("test_output.txt");
		std::unique_ptr<Test::Output> output(new Test::TextOutput(Test::TextOutput::Verbose, outfile));
		Test::Suite tests;
		tests.add(new MemoryMappedFileTest());
		tests.add(new IPCMutexTest());
		tests.add(new FixedMemoryHashTest());
		tests.add(new FixedMemoryVariableHashTest());
		tests.add(new atoboolTest());
		tests.add(new hextoi_32_64_Test());
		tests.add(new StringUtilTest());
		tests.add(new DataVerificationTest());
		tests.add(new SkillsUtilsTest());
		tests.run(*output, true);
	} catch (...) {
		std::cout << "Tests failed" << std::endl;
		return -1;
	}
	std::cout << "Tests completed successfully" << std::endl;
	return 0;
}
