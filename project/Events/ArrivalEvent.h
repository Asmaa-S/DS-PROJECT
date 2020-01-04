#pragma once

#include "Event.h"


//class for the arrival event
class ArrivalEvent: public Event
{
	//info about the order ralted to arrival event
	int OrdDishes;	//order number of dishes
	ORD_TYPE OrdType;		//order type: Normal, Vegan, VIP	                
	double OrdMoney;	//Total order money
	int AutoS; // represent the number of timesteps after which an order is automatically promoted to VIP
public:
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType);
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType,int size, double money, int autoS);
	//Add more constructors if needed
	
	virtual void Execute(Restaurant *pRest);	//override execute function

};

