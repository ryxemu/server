#include "uuid.h"

#ifdef WIN32
#include <rpc.h>
#else
#include <uuid/uuid.h>
#endif

std::string CreateUUID() {
#ifdef WIN32
	UUID uuid;
	/*
	C6031	Return value ignored
	Return value ignored: 'UuidCreate'.	common	uuid.cpp	31

	C6102		Using 'uuid' from failed function call at line '31'.	common	uuid.cpp	33
	'uuid' is not initialized			31
	'uuid' is an Input to 'UuidToStringA'
	(declared at c:\program files (x86)\windows kits\8.1\include\shared\rpcdce.h:2496)			33
	'uuid' is used, but may not have been initialized			33

	C6102		Using 'str' from failed function call at line '33'.	common	uuid.cpp	34
	'str' is not initialized			33
	'str' is an In/Out argument to 'std::basic_string<char,std::char_traits<char>,std::allocator<char> >::{ctor}'
	(declared at c:\program files (x86)\microsoft visual studio 12.0\vc\include\xstring:778)			34
	'str' is used, but may not have been initialized			34
	*/
	UuidCreate(&uuid);
	unsigned char *str = nullptr;
	UuidToStringA(&uuid, &str);
	std::string s((char *)str);
	RpcStringFreeA(&str);
	return s;
#else
	char str[64] = {0};
	uuid_t uuid;
	uuid_generate_random(uuid);
	uuid_unparse(uuid, str);
	return str;
#endif
}
