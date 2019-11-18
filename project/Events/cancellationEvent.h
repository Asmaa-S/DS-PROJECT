#pragma once
#include "..\Defs.h"
#include "Event.h"
#include "..\Rest\Restaurant.h"

class cancellationEvent:public Event
{
	ORD_TYPE oT;
public:
	cancellationEvent(int eTime, int oID);
	~cancellationEvent();
	virtual void Execute(Restaurant *pRest);

};

