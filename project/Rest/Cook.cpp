#include "Cook.h"


Cook::Cook()
{
}

Cook::Cook(int id, ORD_TYPE typ, int sp, int br,int bm)
{
	ID = id; 
	type = typ;
	speed = sp;
	break_duration = br;
	nOfOrdersBeforeBreak = bm;
	state = 0;
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
void Cook::give_order(Order &o) {
	//check state. if free, change state of cook to busy, change state of order to done.
}
void Cook::put_on_break() {
	state = -1;
}
void Cook::mealsDecrement()
{
	mealsIncrement--;

}
void Cook::mealNewIncrement()
{
	mealsIncrement = nOfOrdersBeforeBreak;
}
int Cook::getmealsIncrement()
{
	return mealsIncrement;
}
int Cook::getState() const
{
	return state;
}
void Cook::setState(int i)
{
	state = i;
}

