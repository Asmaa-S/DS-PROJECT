#include "promotionEvent.h"
#include "..\Defs.h"

//etime is when the promotion event is requested
promotionEvent:: promotionEvent(int eTime, int oID, double extraMon) :Event(eTime, oID)
{
	
	extraMoney = extraMon;
	et = P;
}


promotionEvent::~promotionEvent()
{
}

void promotionEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1
	//get the data using the id
	//finding order in the normal orders
	//pRest->normalorders.Find

	//Order ord(EventTime, OrderID, OrdType, OrdDishes, OrdMoney);
	//pRest->viporders.InsertSortedOrder(ord);
	return; //until phase 2

}