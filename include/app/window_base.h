#ifndef WINDOW_BASE_H
#define WINDOW_BASE_H

#include <imgui.h>

class WindowBase
{
public:
	WindowBase() = delete;
	WindowBase(const char* title, bool is_active, enum ImGuiWindowFlags_ flags = ImGuiWindowFlags_MenuBar);
	virtual ~WindowBase() { ; }

	virtual void update() final;

	const char* get_title() const { return title_; }

	void set_title(const char* title) { title_ = title; }

	bool is_active_ = true;

private:
	virtual void handle_context() = 0;

	const char* title_;
	enum ImGuiWindowFlags_ flags_;
};

#endif // !WINDOW_BASE_H