#ifndef UI_UTILS_H
#define UI_UTILS_H

#include <imgui.h>

namespace Utils
{
    namespace Gui
    {
        void help_marker(const char *description);

        void center_cursor(const char* content, const bool center_x, const bool center_y);

    } // namespace Gui

} // namespace Utils

#endif