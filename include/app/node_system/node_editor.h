#ifndef NODE_SYSTEM_H
#define NODE_SYSTEM_H

#include <imgui.h>
#include <imnodes.h>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <ui_utils.h>
#include <nodes.h>
#include <link.h>
#include <notification.h>
#include <app_base.h>
#include <assert.h>


class NodeEditor {
public:
	NodeEditor();

	~NodeEditor();

	bool serialize() { ; }

	bool deserialize() { ; }

	void render();

	void render_elements();

	void render_minimap_menu();

	void render_menu_bar();

	void render_popups();

	void render_debug_window();

	void add_node(Node* node);

	void link();

	Link* get_link(int unique_link_id) const;

	Node* get_node(int unique_node_id) const;

	void add_link(int input_pin, int output_pin);

	void remove_node(Node* node);

	void remove_node(int unique_node_id_);

	void remove_link(Link* link);

	void remove_link(int unique_link_id_);

	void remove_link(Node* node);

	void remove_link_having_pin(int unique_pin_id);

	int get_pin_occurence(int unique_pin_id);

	bool pin_has_link(int unique_pin_id);

	bool link_has_pin(int unique_link_id);

	// callback functions
	friend void minimap_hovering_callback(int node_id, void* user_data);
	void link_hovering_callback();
	void background_hovering_callback();
	void nodes_hovering_callback();
	void zoom_callback();


private:
	std::vector<Node*> nodes_;
	std::vector<Link*> links_;

	ImVec2 mouse_pos_ = ImGui::GetMousePos();

	// debug window
	bool show_debug_window_ = true;

	// zoom
	float zoom_ = 1.0f;
	float zoom_min_ = 0.1f;
	float zoom_max_ = 3.0f;
	float zoom_sensitivity_ = 0.1f;

	// minimap
	ImNodesMiniMapLocation minimap_location_ = ImNodesMiniMapLocation_TopRight;
	bool show_minimap_ = true;

	// about nodes
	bool is_node_hovered_ = false;
	bool is_link_hovered_ = false;
	bool is_node_created_ = false;

	int hovered_link_id_ = -1;
	int hovered_node_id_ = -1;

	// ids managment
	static int unique_attribute_;
	static int unique_link_id_;
	static int unique_node_id_;

};

#endif