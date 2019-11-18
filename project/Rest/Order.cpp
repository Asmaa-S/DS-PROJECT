#include "Order.h"

Order::Order()
{
}

Order::Order(int id, ORD_TYPE r_Type)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	status = WAIT;
	if (r_Type == TYPE_VIP)
		vip_priority = int(totalMoney) - Dishes - ArrTime;

}

Order::~Order()
{
}

int Order::get_stept_bef_autopromote()
{
	if (type == TYPE_NRM)
		return steps_bef_autopromote;
	else
		return -1;
}

void Order::set_stept_bef_autopromote(int s)
{
	if (type == TYPE_NRM)
	steps_bef_autopromote = s;
	else
		steps_bef_autopromote =-1;
}

int Order::GetID()
{
	return ID;
}


ORD_TYPE Order::GetType() const
{
	return type;
}


void Order::SetDishes(int d)
{
	Dishes = d>0?d:0;
}

int Order::GetDishes() const
{
	return Dishes;
}

void Order::SetFinish(int d)
{
	FinishTime = d;
}

int Order::GetFinish() const
{
	return FinishTime;
}

void Order::setAT(int s)
{
	ArrTime = s;
}

int Order::getAT() const
{
	return ArrTime;
}

void Order::setST(int s)
{
	ServTime = s;
}

int Order::getST() const
{
	return ServTime;
}


void Order::setStatus(ORD_STATUS s)
{
	status = s;
}

ORD_STATUS Order::getStatus() const
{
	return status;
}

