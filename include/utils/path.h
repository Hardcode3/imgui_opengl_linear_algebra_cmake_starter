#ifndef PATH_H
#define PATH_H

#include <string>
#include <filesystem>
#include <assert.h>

namespace Utils
{
	namespace Path
	{
		// path generation
		const char* convert_to_c_path(const std::string& path);

		// file handling
		bool file_exists(const std::string& filename);
	
	}
	namespace Str
	{
		const char* concatenate_cstr(const char* str1, const char* str2);
	}
}

#endif // !PATH_H
