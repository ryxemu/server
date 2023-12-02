#include <fstream>
#include "file_util.h"

#ifdef _WINDOWS
#include <direct.h>
#include <conio.h>
#include <iostream>
#include <dos.h>
#include <windows.h>
#include <process.h>
#else

#include <unistd.h>
#include <sys/stat.h>

#endif

/**
 * @param name
 * @return
 */
bool FileUtil::exists(const std::string& name) {
	std::ifstream f(name.c_str());

	return f.good();
}

/**
 * @param directory_name
 */
void FileUtil::mkdir(const std::string& directory_name) {
#ifdef _WINDOWS
	struct _stat st;
	if (_stat(directory_name.c_str(), &st) == 0)  // exists
		return;
	_mkdir(directory_name.c_str());
#else
	struct stat st {};
	if (stat(directory_name.c_str(), &st) == 0) {  // exists
		return;
	}
	::mkdir(directory_name.c_str(), 0755);
#endif
}