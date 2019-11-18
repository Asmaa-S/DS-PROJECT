#include "promotionEvent.h"
#include "..\Defs.h"


promotionEvent:: promotionEvent(int eTime, int oID, double mon) :Event(eTime, oID)
{
	
	money = mon;
	et = P;
}


promotionEvent::~promotionEvent()
{
}

void promotionEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1

}