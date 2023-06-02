#ifndef NODES_H
#define NODES_H

#include <imgui.h>
#include <imnodes.h>
#include <vector>
#include <ui_utils.h>


enum NodeType 
{
	Model,
	Anisotropy,
	Solver,
	RayTracing
};

enum PinType
{
	Out,
	In
};

const int get_available_pin_id();
const int get_available_node_id();


struct Pin
{
	Pin(NodeType compatibility, PinType pin_type, int nb_connexions);
	~Pin() { ; }

	int unique_id_;
	int nb_connexions_;
	PinType type_;
	NodeType compatibility_;
};


class Node {
public:
	Node(ImVec2& position, NodeType node_type);
	virtual ~Node();

	virtual void draw_node() = 0;
	//virtual void* run() = 0;

	// getters
	const int& get_unique_id() const { return id_; }

	std::vector<Pin*>& get_pins() { return pins_; }

	NodeType& get_type() { return type_; }

	const int get_pin_number() const { return pins_.size(); }
	
	// end getters

protected:
	// store the type of the node and the compatibility with other nodes
	NodeType type_;
	std::vector<Pin*> pins_;
	ImVec2 position_;
	int id_;
};


class SynthNullModelNode : public Node {
public:
	SynthNullModelNode(ImVec2 position = ImVec2(0, 0));

	void draw_node() override;

private:
	int out_model_ = -1;
};


class SynthLinearModelNode : public Node {
public:
	SynthLinearModelNode(ImVec2 position = ImVec2(0, 0));

	void draw_node() override;

	void set_basis(int new_basis) { basis_ = new_basis; }
	void set_gradient(float new_gradient) { gradient_ = new_gradient; }

	const int get_basis() const { return basis_; }
	const float get_gradient() const { return gradient_; }

private:
	int basis_ = 2000;
	float gradient_ = 0.88;

	int out_model_ = -1;
};


class IsotropyNode : public Node 
{
public:
	IsotropyNode(ImVec2 position = ImVec2(0, 0));

	void draw_node() override;

private:
	int in_velocity_mdl_ = -1;
	int out_ray_tracing_ = -1;
};


class VTINode : public Node
{
public:
	VTINode(ImVec2 position = ImVec2(0, 0));

	void draw_node() override;

private:

};
#endif // !NODES_H
