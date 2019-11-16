#include "Cook.h"


Cook::Cook()
{
}

Cook::Cook(int id, ORD_TYPE typ, int sp, int br)
{
	ID = id; 
	type = typ;
	speed = sp;
	break_duration = br;
}


Cook::~Cook()
{
}


int Cook::GetID() const
{
	return ID;
}


ORD_TYPE Cook::GetType() const
{
	return type;
}


void Cook::setID(int id)
{
	ID = id;
}

void Cook::setType(ORD_TYPE t)
{
	type = t;
}
void Cook::give_order(Order &o) {
	//check state. if free, change state of cook to busy, change state of order to done.
}
void Cook::put_on_break() {
	state = -1;
}

