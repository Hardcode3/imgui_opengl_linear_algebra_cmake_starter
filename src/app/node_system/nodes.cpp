#include <nodes.h>

static int unique_attribute_ = -1;
static int unique_node_id_ = -1;

const int get_available_pin_id()
{
	unique_attribute_++;
	return unique_attribute_;
}

const int get_available_node_id()
{
	unique_node_id_++;
	return unique_node_id_;
}


Pin::Pin(NodeType compatibility, PinType pin_type, int nb_connexions) : compatibility_(compatibility), type_(pin_type), nb_connexions_(nb_connexions)
{ 
	unique_id_ = get_available_pin_id();
}


Node::Node(ImVec2& position, NodeType node_type) : type_(node_type), position_(position)
{
	id_ = get_available_node_id();
}

Node::~Node()
{
	for (auto& pin : pins_)
	{
		delete pin;
	}
}


SynthNullModelNode::SynthNullModelNode(ImVec2 position): Node(position, NodeType::Model)
{
	pins_.push_back(new Pin(Anisotropy, Out, 1));
}

void SynthNullModelNode::draw_node() 
{
	ImNodes::BeginNode(get_unique_id());

	ImNodes::BeginNodeTitleBar();
	ImGui::Text("%s", "Null model");
	ImNodes::EndNodeTitleBar();

	ImNodes::BeginOutputAttribute(pins_[0]->unique_id_);
	ImGui::Indent(0);
	ImGui::Text("out");
	ImNodes::EndOutputAttribute();

	ImNodes::EndNode();
}

SynthLinearModelNode::SynthLinearModelNode(ImVec2 position) : Node(position, NodeType::Model)
{
	pins_.push_back(new Pin(Anisotropy, Out, 1));
}

void SynthLinearModelNode::draw_node() 
{
	ImNodes::BeginNode(get_unique_id());

	ImNodes::BeginNodeTitleBar();
	ImGui::Text("%s", "Linear Model");
	ImGui::SameLine();
	Utils::Gui::help_marker("Constructs a linear model that depends on the depth.\nWith this node, you can build linearly increasing geophysical models: velocity, anisotropy...");
	ImNodes::EndNodeTitleBar();

	ImNodes::BeginOutputAttribute(pins_[0]->unique_id_);
	ImGui::Indent(0);
	
	ImGui::SetNextItemWidth(200.0f);
	ImGui::SliderInt("Basis", &basis_, 1000, 4000);
	ImGui::SameLine();
	Utils::Gui::help_marker("Choose the basis, i.e. the value taken by the model at a null depth.\n It can also be called ordinate at the origin.");

	ImGui::SetNextItemWidth(200.0f);
	ImGui::SliderFloat("Gradient", &gradient_, 0.2f, 10.0f);
	ImGui::SameLine();
	Utils::Gui::help_marker("Choose the gradient of the model, i.e. the increase in value per distance unit.");

	ImNodes::EndOutputAttribute();

	ImNodes::EndNode();
}

IsotropyNode::IsotropyNode(ImVec2 position): Node(position, NodeType::Anisotropy)
{
	pins_.push_back(new Pin(Model, In, 1));
	pins_.push_back(new Pin(RayTracing, Out, 1));
}

void IsotropyNode::draw_node()
{
	ImNodes::BeginNode(get_unique_id());

	ImNodes::BeginNodeTitleBar();
	ImGui::Text("%s", "Isotropy Model");
	ImGui::SameLine();
	Utils::Gui::help_marker("Constructs an isotropy model for ray tracing.\n The geophysical values can depend on the position but not on the propagation direction.\n(c.f. the defition of the anisotropy)");
	ImNodes::EndNodeTitleBar();

	ImNodes::BeginInputAttribute(pins_[0]->unique_id_);
	ImGui::Indent(0);
	ImGui::Text("Velocity");
	ImGui::SameLine();
	Utils::Gui::help_marker("The velocity model (can be null, constant, linear...))");
	ImNodes::EndInputAttribute();
	
	ImGui::Text("");

	ImNodes::BeginOutputAttribute(pins_[1]->unique_id_);
	ImGui::Indent(0);
	ImGui::Text("Ray Tracing");
	ImGui::SameLine();
	Utils::Gui::help_marker("The ray tracing node that is going to run the computations.");
	ImNodes::EndOutputAttribute();

	ImNodes::EndNode();
}

VTINode::VTINode(ImVec2 position) : Node(position, NodeType::Anisotropy)
{
	pins_.push_back(new Pin(Model, In, 1));
	pins_.push_back(new Pin(Model, In, 1));
	pins_.push_back(new Pin(Model, In, 1));
	pins_.push_back(new Pin(RayTracing, Out, 1));
}

void VTINode::draw_node()
{
	ImNodes::BeginNode(get_unique_id());

	ImNodes::BeginNodeTitleBar();
	ImGui::Text("%s", "VTI Model");
	ImGui::SameLine();
	Utils::Gui::help_marker("Constructs an isotropy model (VTI) for ray tracing.\n The geophysical values can depend on the position but not on the propagation direction.\n(c.f. the defition of the anisotropy)");
	ImNodes::EndNodeTitleBar();

	ImNodes::BeginInputAttribute(pins_[0]->unique_id_);
	ImGui::Indent(0);
	ImGui::Text("Velocity");
	ImGui::SameLine();
	Utils::Gui::help_marker("The velocity model (can be null, constant, linear...))");
	ImNodes::EndInputAttribute();

	ImNodes::BeginInputAttribute(pins_[1]->unique_id_);
	ImGui::Indent(0);
	ImGui::Text("Epsilon");
	ImGui::SameLine();
	Utils::Gui::help_marker("The epsilon model (can be null, constant, linear...))");
	ImNodes::EndInputAttribute();

	ImNodes::BeginInputAttribute(pins_[2]->unique_id_);
	ImGui::Indent(0);
	ImGui::Text("Delta");
	ImGui::SameLine();
	Utils::Gui::help_marker("The delta model (can be null, constant, linear...))");
	ImNodes::EndInputAttribute();

	ImGui::Text("");

	ImNodes::BeginOutputAttribute(pins_[3]->unique_id_);
	ImGui::Indent(0);
	ImGui::Text("Ray Tracing");
	ImGui::SameLine();
	Utils::Gui::help_marker("The ray tracing node that is going to run the computations.");
	ImNodes::EndOutputAttribute();

	ImNodes::EndNode();
}