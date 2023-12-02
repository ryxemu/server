#ifndef _WINDOWS
#ifndef __UNIX_H__
#define __UNIX_H__
#include <unistd.h>

typedef int SOCKET;

void Sleep(unsigned int x);
#ifndef __CYGWIN__
char* strupr(char* tmp);
char* strlwr(char* tmp);
#endif
#endif
#endif
