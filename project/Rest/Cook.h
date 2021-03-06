#pragma once

#include "..\Defs.h"
#include "Order.h"
#pragma once
class Cook
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding type (VIP, Normal, Vegan)
	int speed;		//dishes it can prepare in one clock tick (in one timestep)
	int break_duration;
	int nOfOrdersBeforeBreak;
	COOK_STATE state; // 0 is free, 1 is busy, -1 is on break
	double orderTime;

	int mealsIncrement;

	int orders_done_bef_break;
	int break_start_time;

public:
	Cook();
	Cook(int id, ORD_TYPE typ, int sp, int br,int bm);
	virtual ~Cook();

	int GetID() const;
	void setID(int i);

	void setType(ORD_TYPE typ);
	ORD_TYPE GetType() const;

	COOK_STATE getState() const;
	void setState(COOK_STATE i);
	
	double getOrderTime() const;
	void setOrderTime(double d);

	int getBreakDuration() const;
	int getSpeed() const;
	int get_break_start_time();
	void give_order(Order &o);
	void put_on_break();

	void mealsDecrement();
	void mealNewIncrement();
	int getmealsIncrement();
	
	void put_on_break(int timestep);
	int get_num_orders_done();
	void increment_orders_done();
	void put_out_of_break();

};
