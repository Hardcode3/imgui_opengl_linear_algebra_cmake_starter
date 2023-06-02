
#include <path.h>

const char* Utils::Path::convert_to_c_path(const std::string& path)
{
    static std::string result = path;
    const char separator = '/';
    const char replacement = '\\';
    size_t pos = 0;
    while ((pos = result.find(separator, pos)) != std::string::npos)
    {
        result.replace(pos, 1, 1, replacement);
        pos += 1;
    }
    return result.c_str();
}

bool Utils::Path::file_exists(const std::string& filename)
{
    return std::filesystem::exists(filename);
}

