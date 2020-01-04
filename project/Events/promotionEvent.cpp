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
	
	//finding order in the normal orders and getting its info
	Order o = pRest->normalorders.getOrder(OrderID);
	int OrdDishes = o.GetDishes();
	double OrdMoney = o.getMoney() + extraMoney;
	//deleting order from normal orders
	pRest->normalorders.DelNode(OrderID);

	//making a new vip order with the same info as the normal one and add it to the vip orders
	Order ord(EventTime, OrderID, OrdType, OrdDishes, OrdMoney);
	pRest->viporders.InsertSortedOrder(ord);

	return; //until phase 2

}