#include "Cook.h"


Cook::Cook()
{
}

Cook::Cook(int id, ORD_TYPE typ, int sp, int br,int bm)
{
	orders_done_bef_break = 0;
	ID = id; 
	type = typ;
	speed = sp;
	break_duration = br;
	nOfOrdersBeforeBreak = bm;
	state = FREE;
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
double Cook::getOrderTime() const
{
	return orderTime;
}
void Cook::setOrderTime(double d)
{
	orderTime = d;
}
int Cook::getBreakDuration() const
{
	return break_duration;
}
int Cook::getSpeed() const
{
	return speed;
}
int Cook::get_break_start_time()
{
	return break_start_time;
}
void Cook::give_order(Order &o) {
	//check state. if free, change state of cook to busy, change state of order to done.
}
void Cook::put_on_break(int timestep) {
	orders_done_bef_break = 0; //reset
	break_start_time = timestep;
	state = ONBREAK;
}
int Cook::get_num_orders_done()
{
	return orders_done_bef_break;
}
void Cook::increment_orders_done()
{
	orders_done_bef_break++;
}
void Cook::put_out_of_break()
{
	break_start_time = -1;
	state = FREE;
}
COOK_STATE Cook::getState() const
{
	return state;
}
void Cook::setState(COOK_STATE i)
{
	state = i;
}

