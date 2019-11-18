#include "cancellationEvent.h"
#include "..\Rest\Restaurant.h"


cancellationEvent::cancellationEvent(int eTime, int oID): Event(eTime, oID)
{
	et = X;

}


cancellationEvent::~cancellationEvent()
{
}


void cancellationEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1
	pRest->getNormalOrders().DeleteNode(ID);
	

}
