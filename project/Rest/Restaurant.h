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

// note: use cooks::increment orders done, whenever an order is assigned to a cook.
//call function handle break every timestep
class Restaurant  
{	
public:
	int n_autopromoted=0;
	int totl_num_orders;
	int totl_num_cooks;
	int n_cooks_veg;
	int n_cooks_norm;
	int n_cooks_vip;
	int meals_bef_break;
	int break_dur_norm, break_dur_veg, break_dur_vip;
	int numOfFinishedOrders = 0;

	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	LinkedList<Cook> normalcookslist;
	LinkedList<Cook> vegancookslist;
	LinkedList<Cook> vipcookslist;
	LinkedList<Cook> busyCooks;
	LinkedList<Cook> inBreakCooks;

	LinkedList<Order> inserviceList;

	Queue<Order> veganorders; 
	LinkedList<Order> normalorders;
	LinkedList<Order> viporders; 

	
	Order* Finished_Orders= new Order [totl_num_orders];

	
	
	Restaurant();
	~Restaurant();
	
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();
	void FillDrawingList();
	bool EventsQueueIsEmpty();
	void handle_cook_breaks(int current_time_step);
	void load_from_file(string filename);
	void save_to_file(string filename);
	LinkedList<Order> getNormalOrders();
	LinkedList<Order> getVipOrders();
	Queue<Order> getVeganOrders();
	LinkedList<Cook> getVipCookList();
	LinkedList<Cook> getVeganCookList();
	LinkedList<Cook> getNormalCookList();


	Order* getFinishedOrders();
	Order* getInserviceList();
	void pickOneOrder();
	void moveToFinished();
	void simpleSimulator();
	void assignVIPOrders();
	void assignNormalOrders();
	void assignVeganOrders();
	void freeCook();
	int getFinishedNumber();
	void addFinishedOrder(Order order);
	void autoPromot(int timeStep)
	{if (normalorders.getCount() == 0)
	{
		return;
	}
	int autoS = normalorders.getHead()->getItem().getAutoS();

	while (normalorders.getCount() > 0)
	{
		Order normalOrd = normalorders.getHead()->getItem();

		if (timeStep - normalOrd.getAT() >= autoS)
		{
			Order VIPOrd(timeStep, normalOrd.GetID(), TYPE_VIP,normalOrd.GetDishes(), normalOrd.getMoney());
			viporders.InsertSortedOrder(VIPOrd);
			normalorders.DeleteFirst();
		}
		else
		{
			break;
		}
	}
	return;
	}
	// TODO: Add More Member Functions As Needed
	//

};
