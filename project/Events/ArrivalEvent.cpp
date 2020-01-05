#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType):Event(eTime, oID)
{
	OrdType = oType;
	et = R;
}
ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, int size, double money, int s) : Event(eTime, oID)
{
	OrdType = oType;
	et = R;
	OrdDishes = size;
	OrdMoney = money;
	AutoS = s;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data 
	// Then adds it to either normal, vegan, or VIP order lists

	Order ord(EventTime,OrderID, OrdType,OrdDishes,OrdMoney);
	
	if (OrdType == TYPE_VEG)
	{
		pRest->veganorders.enqueue(ord);
	}
	else if (OrdType == TYPE_NRM)
	{
		ord.setAutoS(AutoS);
		pRest->normalorders.InsertEnd(ord);
	}
	else if (OrdType == TYPE_VIP)
	{
		pRest->viporders.InsertSortedOrder(ord);
	}
}
