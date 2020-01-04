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

	void give_order(Order &o);
	void put_on_break();


};
