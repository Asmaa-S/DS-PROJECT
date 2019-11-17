#pragma once

#include "..\Defs.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include "..\Events\cancellationEvent.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Events\promotionEvent.h"
#include "..\Generic_DS\LinkedList.h"
#include "..\Generic_DS\Stack.h"
#include "Cook.h"
#include "Order.h"
#include <string.h>
#include<fstream>
#include <stdio.h>
#include<algorithm>
#include <time.h> 
#include <sstream> 
// it is the maestro of the project
class Restaurant  
{	
private:
	int n_autopromoted=0;
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	LinkedList<Cook> normalcookslist;
	LinkedList<Cook> vegancookslist;
	LinkedList<Cook> vipcookslist;

	Queue<Order> veganorders;
	LinkedList<Order> normalorders;
	LinkedList<Order> viporders; //

	Queue<Order> Finished_Orders;
	//
	// TODO: Add More Data Members As Needed
	//


public:
	
	Restaurant();
	~Restaurant();
	
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	void FillDrawingList();
	bool EventsQueueIsEmpty();
	void load_from_file(string filename);
	void save_to_file(string filename);
	//
	// TODO: Add More Member Functions As Needed
	//

};
