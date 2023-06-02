#ifndef TABLE_UTILS_H
#define TABLE_UTILS_H

#include <imgui.h>
#include <string>
#include <vector>

namespace Utils
{
	namespace Gui
	{
		void display_table(const char *title, bool *p_open, const std::vector<std::vector<float>> &data, const std::vector<std::string> &header, ImGuiWindowFlags flags = 0);
	}
}

#endif