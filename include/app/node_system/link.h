#ifndef LINK_H
#define LINK_H

const int get_available_link_id();

struct Link
{
	Link(int input_pin, int output_pin);
	~Link() { ; }

	int id_;
	int input_slot_id_ = -1;
	int output_slot_id_ = -1;
};


#endif // !LINK_H
