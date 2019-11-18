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
#include "..\GUI\GUIDrawables\NormalGUIElement.h"
#include "..\GUI\GUIDrawables\VeganGUIElement.h"
#include "..\GUI\GUIDrawables\VIPGUIElement.h"
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
	Order inserviceList[100];
	Queue<Order> veganorders;

public:
	Queue<Order> veganorders; //7atenahom public 3lshan elarrival wl cancelation events // check them back b2a

	LinkedList<Order> normalorders;
	LinkedList<Order> viporders; //
	Queue<Order> Finished_Orders;
	int inservice;
	//
	// TODO: Add More Data Members As Needed
	//


//public:
	
	Restaurant();
	~Restaurant();
	
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();
	void FillDrawingList();
	bool EventsQueueIsEmpty();
	void load_from_file(string filename);
	void save_to_file(string filename);
	LinkedList<Order> getNormalOrders();
	LinkedList<Order> getVipOrders();
	Queue<Order> getVeganOrders();
	Queue<Order> getFinishedOrders();
	Order getInserviceList();
	void pickOneOrder();

	// TODO: Add More Member Functions As Needed
	//

};
