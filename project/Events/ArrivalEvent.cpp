#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType):Event(eTime, oID)
{
	OrdType = oType;
	et = R;
}
ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, int size, double money) : Event(eTime, oID)
{
	OrdType = oType;
	et = R;
	OrdDishes = size;
	OrdMoney = money;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1
	// Then adds it to either normal, vegan, or VIP order lists

	Order ord(EventTime,OrderID, OrdType,OrdDishes,OrdMoney); 
	if (OrdType == TYPE_VEG)
	{
		pRest->veganorders.enqueue(ord);
	}
	else if (OrdType == TYPE_NRM)
	{
		pRest->normalorders.InsertEnd(ord);
	}
	else if (OrdType == TYPE_VIP)
	{
		pRest->viporders.InsertEnd(ord); // needs to be edited
	}
}
