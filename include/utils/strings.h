#ifndef STRINGS_H
#define STRINGS_H

#include <string>
#include <assert.h>

namespace Utils
{
	namespace Str
	{
		const char* concatenate_cstr(const char* str1, const char* str2, char* result);
	}
}

#endif // !STRINGS_H