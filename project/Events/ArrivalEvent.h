#pragma once

#include "Event.h"


//class for the arrival event
class ArrivalEvent: public Event
{
	//info about the order ralted to arrival event
	int OrdDishes;	//order number of dishes
	ORD_TYPE OrdType;		//order type: Normal, Vegan, VIP	                
	double OrdMoney;	//Total order money
public:
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType);
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType,int size, double money);
	//Add more constructors if needed
	
	virtual void Execute(Restaurant *pRest);	//override execute function

};

