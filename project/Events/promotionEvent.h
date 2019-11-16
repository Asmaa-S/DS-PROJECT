#pragma once
#include "Event.h"
#include "..\Defs.h"
#include "..\Rest\Restaurant.h"
class promotionEvent :
	public Event
{

	ORD_TYPE OrdType;
	double money;
public:
	promotionEvent(int eTime, int oID, double mon);
	~promotionEvent();
	virtual void Execute(Restaurant *pRest);
};

