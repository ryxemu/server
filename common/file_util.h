#ifndef EQEMU_FILE_UTIL_H
#define EQEMU_FILE_UTIL_H

class FileUtil {
   public:
	static bool exists(const std::string& name);
	static void mkdir(const std::string& directory_name);
};

#endif  // EQEMU_FILE_UTIL_H