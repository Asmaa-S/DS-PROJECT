#pragma once
#include "Event.h"
#include "..\Defs.h"
#include "..\Rest\Restaurant.h"
class promotionEvent :
	public Event
{

	ORD_TYPE OrdType = TYPE_VIP;
	double extraMoney;
public:
	promotionEvent(int eTime, int oID, double extraMon);
	~promotionEvent();
	virtual void Execute(Restaurant *pRest);
};

