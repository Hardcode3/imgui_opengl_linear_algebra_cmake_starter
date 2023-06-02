#include <link.h>

static int unique_link_id_ = -1;

const int get_available_link_id()
{
	unique_link_id_++;
	return unique_link_id_;
}

Link::Link(int input_pin, int output_pin)
{
	id_ = get_available_link_id();
	input_slot_id_ = input_pin;
	output_slot_id_ = output_pin;
}