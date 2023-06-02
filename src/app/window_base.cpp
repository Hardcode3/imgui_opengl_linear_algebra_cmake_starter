#include <window_base.h>
#include <imgui.h>


WindowBase::WindowBase(const char* title, bool is_active, enum ImGuiWindowFlags_ flags) :title_(title), flags_(flags) 
{
	is_active_ = is_active;
}

void WindowBase::update()
{
	if (is_active_)
	{
		ImGui::Begin(title_, &is_active_, ImGuiWindowFlags_MenuBar);
		handle_context();
		ImGui::End();
	}
}

