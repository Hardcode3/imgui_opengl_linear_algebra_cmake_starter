#include <strings.h>
#include <iostream>
#include <cstring>

bool test_concatenate_cstr(bool verbose)
{
	const char* str1 = "hello ";
	const char* str2 = "world !";
	char sum[200];
	Utils::Str::concatenate_cstr(str1, str2, sum);
	if (verbose)
	{
		std::cout << "sum " << sum << std::endl;
		std::cout << "--- " << "hello world !" << std::endl;
		std::cout << "strcomp result " << strcmp(sum, "hello world !") << std::endl;
	}
	if (strcmp(sum, "hello world !") == 0)
		return true;
	return false;
}


int main()
{
	const bool verbose = true;
	if (test_concatenate_cstr(verbose))
		return 0;
	return 1;
}