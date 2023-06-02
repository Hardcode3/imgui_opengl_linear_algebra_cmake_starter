#include <strings.h>

const char* Utils::Str::concatenate_cstr(const char* str1, const char* str2, char* result)
{
    size_t len1 = std::strlen(str1);
    size_t len2 = std::strlen(str2);
    size_t len_result = std::strlen(result);
    
    // test if the result array buffer is enough large for the two input array
    // and the termination character
    if (len1 + len2 + 1 > len_result)
        return "CSTR_CONCATENATION_FAILURE";

    // copy the strings into the new array
    std::memcpy(result, str1, len1);
    std::memcpy(result + len1, str2, len2 + 1);

    return result;
}