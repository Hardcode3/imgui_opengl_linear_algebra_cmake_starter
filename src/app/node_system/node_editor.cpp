#include <node_editor.h>

void minimap_hovering_callback(int node_id, void* user_data)
{
	NodeEditor* node_editor_ptr = static_cast<NodeEditor*>(user_data);

	ImGui::SetTooltip("Click to center the node %d", node_id);

	if (ImGui::IsMouseClicked(1) && ImGui::IsWindowHovered())
	{
		// right click on a node in the node editor
	}
}

void NodeEditor::link_hovering_callback()
{
	if (is_link_hovered_)
	{
		if(ImGui::IsMouseDown(1))
			ImGui::OpenPopup("LinkPopup");
	}
}

void NodeEditor::background_hovering_callback()
{
	if (ImGui::IsMouseClicked(1) && ImGui::IsWindowHovered() && !is_node_hovered_)
	{
		ImGui::OpenPopup("BackgroundPopup");
	}
}

void NodeEditor::nodes_hovering_callback()
{
	if (ImGui::IsMouseClicked(1) && ImGui::IsWindowHovered() && is_node_hovered_)
	{
		ImGui::OpenPopup("NodePopup");
		std::cout << "hoovered node id" << hovered_node_id_ << std::endl;
	}
}

void NodeEditor::zoom_callback()
{
	static float wheel_delta = ImGui::GetIO().MouseWheel;
	zoom_ += wheel_delta * zoom_sensitivity_;
	if (zoom_ > zoom_max_)
		zoom_ = zoom_max_;
	else if (zoom_ < zoom_min_)
		zoom_ = zoom_min_;
	// not available in imnodes...
}

NodeEditor::NodeEditor() {
	ImNodes::StyleColorsDark();
	ImNodes::SetCurrentContext(ImNodes::CreateContext());
}

NodeEditor::~NodeEditor() {
	for (auto node : nodes_) 
	{
		delete node;
	}
	
	for (auto link : links_)
	{
		delete link;
	}
	
	nodes_.clear();
	links_.clear();

}

void NodeEditor::render_minimap_menu()
{
	if (ImGui::BeginMenu("Minimap"))
	{
		ImGui::Checkbox("Show minimap", &show_minimap_);
		if (ImGui::BeginMenu("Position"))
		{
			if (ImGui::MenuItem("Top right"))
			{
				minimap_location_ = ImNodesMiniMapLocation_TopRight;
			}
			if (ImGui::MenuItem("Top left"))
			{
				minimap_location_ = ImNodesMiniMapLocation_TopLeft;
			}
			if (ImGui::MenuItem("Bottom right"))
			{
				minimap_location_ = ImNodesMiniMapLocation_BottomRight;
			}
			if (ImGui::MenuItem("Bottom left"))
			{
				minimap_location_ = ImNodesMiniMapLocation_BottomLeft;
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
}

void NodeEditor::link()
{
	int start_attr, end_attr;
	if (ImNodes::IsLinkCreated(&start_attr, &end_attr))
	{
		add_link(start_attr, end_attr);
	}
	
	int link_id;
	if (ImNodes::IsLinkDestroyed(&link_id))
	{
		remove_link(link_id);
	}
}

void NodeEditor::render_elements()
{
	for (auto& node : nodes_)
	{
		node->draw_node();
	}
	for (auto& link : links_)
	{
		ImNodes::Link(link->id_, link->input_slot_id_, link->output_slot_id_);
	}
}

void NodeEditor::render_menu_bar()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Load"))
				;
			if (ImGui::MenuItem("Save"))
				;
			if (ImGui::MenuItem("Close"))
				;

			ImGui::EndMenu();
		}
		ImGui::Checkbox("Debug", &show_debug_window_);
		render_minimap_menu();

		ImGui::EndMenuBar();
	}
}

void NodeEditor::render() 
{
	mouse_pos_ = ImGui::GetMousePos();
	
	render_menu_bar();
	if (show_debug_window_)
		render_debug_window();

	ImNodes::BeginNodeEditor();

	render_elements();

	link_hovering_callback();
	background_hovering_callback();
	nodes_hovering_callback();
	
	if (show_minimap_)
		ImNodes::MiniMap(0.2f, minimap_location_, minimap_hovering_callback, static_cast<void*>(this));
	
	render_popups();

	ImNodes::EndNodeEditor();

	link();
	
	is_link_hovered_ = ImNodes::IsLinkHovered(&hovered_link_id_);
	is_node_hovered_ = ImNodes::IsNodeHovered(&hovered_node_id_);
}

void NodeEditor::render_popups()
{
	if (ImGui::BeginPopup("BackgroundPopup"))
	{
		if (ImGui::BeginMenu("   Model"))
		{
			if (ImGui::BeginMenu("   Synthetic"))
			{
				if (ImGui::MenuItem("   Null")) {
					add_node(new SynthNullModelNode(mouse_pos_));
					notif_sys.insert_notification("Added node", ImVec4(0, 1, 0, 1), 2000);
					std::cout << "ne notification system@ " << &notif_sys << std::endl;
				}
				if (ImGui::MenuItem("   Binary")) {
					notif_sys.insert_notification("Added binary model\n", ImVec4(0, 1, 0, 1), 4000);
				}
				if (ImGui::MenuItem("   Linear")) {
					add_node(new SynthLinearModelNode(mouse_pos_));
				}
				if (ImGui::MenuItem("   Quadratic")) {
					// TODO
				}
				if (ImGui::MenuItem("   Polynomial")) {
					// TODO
				}
				ImGui::EndMenu();
			}
			if (ImGui::MenuItem("   B-Splines"))
			{
				;
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("   Anisotropy"))
		{
			if (ImGui::MenuItem("   Isotropy")) {
				add_node(new IsotropyNode(mouse_pos_));
			}
			if (ImGui::MenuItem("   VTI")) {
				add_node(new VTINode(mouse_pos_));
			}
			ImGui::EndMenu();
		}
		ImGui::EndPopup();
	}

	if (ImGui::BeginPopup("NodePopup"))
	{
		if (ImGui::Button("   Delete"))
		{
			if (hovered_node_id_ != -1)
			{
				remove_node(hovered_node_id_);
				notif_sys.insert_notification("Deleted node", ImVec4(1, 0, 0, 1), 2000);
			}
			ImGui::CloseCurrentPopup();
		}
			
		ImGui::EndPopup();
	}		

	if (ImGui::BeginPopup("LinkPopup"))
	{
		if (ImGui::Button("    Delete"))
		{
			if (hovered_link_id_ > -1)
			{
				remove_link(hovered_link_id_);
				notif_sys.insert_notification("Deleted link", ImVec4(1, 0, 0, 1), 2000);
			}
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
}

void NodeEditor::render_debug_window()
{
	ImGui::Begin("Node Editor Debug", &show_debug_window_, ImGuiWindowFlags_NoBringToFrontOnFocus || ImGuiWindowFlags_NoFocusOnAppearing);
	ImGui::Text("This window is useful for devs to debug the node editor");
	ImGui::Separator();
	ImGui::BulletText("Last hovered node id %i", hovered_node_id_);
	ImGui::BulletText("Last hovered link id %i", hovered_link_id_);
	ImGui::Separator();
	ImGui::BulletText("Number of nodes %i", nodes_.size());
	ImGui::Separator();
	ImGui::BulletText("Number of links %i", links_.size());
	ImGui::Separator();
	ImGui::End();
}


Link* NodeEditor::get_link(int unique_link_id) const
{
	for (auto& link : links_)
	{
		if (link->id_ == unique_link_id)
			return link;
	}
	return nullptr;
}

Node* NodeEditor::get_node(int unique_node_id) const
{
	for (auto& node : nodes_)
	{
		if (node->get_unique_id() == unique_node_id)
			return node;
	}
	return nullptr;
}

void NodeEditor::add_node(Node* node) 
{
	nodes_.push_back(node);
}

void NodeEditor::add_link(int input_pin, int output_pin)
{
	links_.push_back(new Link(input_pin, output_pin));
}

void NodeEditor::remove_node(Node* node) 
{
	auto it = std::find(nodes_.begin(), nodes_.end(), node);
	if (it != nodes_.end()) {
		// remove the links created with the node
		remove_link(node);
		// delete the actual node
		assert(*it != nullptr);
		delete* it;
		nodes_.erase(it);
	}
}

void NodeEditor::remove_node(int unique_node_id) 
{
	Node* tmp = get_node(unique_node_id);
	if(tmp != nullptr)
		remove_node(tmp);
}

// removes all the links attached to a specific node
void NodeEditor::remove_link(Node* node)
{
	for (auto& pin : node->get_pins())
	{
		remove_link_having_pin(pin->unique_id_);
	}
}

// removes a link based on its pointer
void NodeEditor::remove_link(Link* link)
{
	auto it = std::find(links_.begin(), links_.end(), link);
	if (it != links_.end())
	{
		assert(*it != nullptr);
		delete* it;
		links_.erase(it);
	}
}

// removes a links having a specific id
void NodeEditor::remove_link(int unique_link_id_)
{
	Link* tmp = get_link(unique_link_id_);
	if (tmp != nullptr)
		remove_link(tmp);
}

// deletes a link having a specific pin id
void NodeEditor::remove_link_having_pin(int unique_pin_id)
{
	for (auto& link : links_)
	{
		if (link->input_slot_id_ == unique_pin_id || link->output_slot_id_ == unique_pin_id)
		{
			remove_link(link);
		}
	}
}

// tells if a pin id correspond to an existing link
bool NodeEditor::pin_has_link(int unique_pin_id)
{
	for (auto& link : links_)
	{
		if (link->input_slot_id_ == unique_pin_id || link->output_slot_id_ == unique_pin_id)
			return true;
	}
	return false;
}

// tells if a link has a specified pin attribute
bool NodeEditor::link_has_pin(int unique_link_id)
{
	Link* tmp = get_link(unique_link_id);
	if (tmp != nullptr)
		if (tmp->input_slot_id_ == unique_link_id || tmp->output_slot_id_ == unique_link_id)
			return true;
	return false;
}

// gets the number of exisiting pin occurrences in links
int NodeEditor::get_pin_occurence(int unique_pin_id)
{
	int occurs = 0;
	for (auto& link: links_)
	{
		if (link->input_slot_id_ == unique_pin_id || link->output_slot_id_ == unique_pin_id)
			++occurs;
	}
	return occurs;
}
