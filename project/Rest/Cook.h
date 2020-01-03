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
	int state; // 0 is free, 1 is busy, -1 is on break

public:
	Cook();
	Cook(int id, ORD_TYPE typ, int sp, int br,int bm);
	virtual ~Cook();

	int GetID() const;
	void setID(int i);

	void setType(ORD_TYPE typ);
	ORD_TYPE GetType() const;

	int getState() const;
	void setState(int i);


	void give_order(Order &o);
	void put_on_break();


};
