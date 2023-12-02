#ifndef _WINDOWS

#include "unix.h"
#include <string.h>
#include <ctype.h>

void Sleep(unsigned int x) {
	if (x > 0)
		usleep(x * 1000);
}

char* strupr(char* tmp) {
	int l = strlen(tmp);
	for (int x = 0; x < l; x++) {
		tmp[x] = toupper(tmp[x]);
	}
	return tmp;
}

char* strlwr(char* tmp) {
	int l = strlen(tmp);
	for (int x = 0; x < l; x++) {
		tmp[x] = tolower(tmp[x]);
	}
	return tmp;
}

#else
int joe = 1;
#endif /* !WIN32 */
