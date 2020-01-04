#include <cstdlib>
#include <time.h>
#include <iostream>
#include "Restaurant.h"
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include<fstream>


void removeSpaces(string &line)
{
	
	int l = line.length(),pos,numsp=0;
	string delim = " ";
	string temp = line;
	//line.clear();
	
	//count spaces
	for (int i = 0; i < l; i++) {
		pos = temp.find(delim);
		if (pos != -1)
		{	
			numsp++;
			temp.erase(0, pos+1);
		}
	}

	for (int i = 0; i< numsp; i++) {
		pos = line.find(delim);
		
		line.erase(pos, 1);
	}
}				   // incremented 
	


Restaurant::Restaurant()
{
	pGUI = NULL;
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE mode = pGUI->getProgramMode();
		
	// If you want to use the simulation GUI you must call initSimMode() same as the demo mode
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		break;
	case MODE_STEP:
		break;
	case MODE_SLNT:
		break;
	case MODE_DEMO:
		pGUI->initSimMode();
		break;
	};

}

void Restaurant::simpleSimulator()
{	// initialize 
	pGUI = new GUI;
	pGUI->initSimMode();
	int step = 1; 

	//loadfile
	load_from_file("Inputfile.txt");


	while (!this->EventsQueueIsEmpty()|| !veganorders.isEmpty() || normalorders.getCount() !=0 || viporders.getCount() !=0 || inserviceList.getCount() != 0)
	{	//update interface
		this->FillDrawingList();
		pGUI->updateInterface();
		pGUI->printStringInStatusBar("Current Time: " + std::to_string(step) + "\n" + "  No Of Vegan Waiting orders: " + std::to_string(veganorders.count()) + "  No Of Normal Waiting orders: " + std::to_string(normalorders.getCount()) + "\n" + "  No Of VIP Waiting orders: " + std::to_string(viporders.getCount()) + "  No Of Available Vegan Cooks: " + std::to_string(vegancookslist.getCount()) + "\n" + "  No Of Available Normal Cooks: " + std::to_string(normalcookslist.getCount()) + "  No Of Available VIP Cooks: " + std::to_string(vipcookslist.getCount()));
		pGUI->handleSimGUIEvents();
		//excute current time step events
		ExecuteEvents(step);
	

		//pick one order
		pickOneOrder();
		/*assignVIPOrders();
		assignVeganOrders();
		assignNormalOrders();
		*/
		//c.	Each 5 timesteps, move an order of each type from In-service list(s) to finished list(s)
		if (step % 5 == 0)
		{
			moveToFinished();
		}

		
		//pGUI->updateInterface();
		pGUI->waitForClick();
		
		step++; //increase time by one
	}

}


void Restaurant::assignVIPOrders()
{
	int cookID, speed, nOfDishes;
	//VIP cooks For VIP orders
	while (vipcookslist.getCount() > 0 &&  viporders.getHead() != nullptr)
	{
		//get the Cook ID of the first waiting Cook
		cookID = vipcookslist.getHead()->getItem().GetID();
		//Set the first Order cook ID and type
		viporders.getHead()->getItem().setCookID(cookID);
		viporders.getHead()->getItem().setCookType(TYPE_VIP);
		//Add the order to inservice List
		speed = vipcookslist.getHead()->getItem().getSpeed();
		inserviceList.insertSortedInserviceOrders(viporders.getHead()->getItem(), speed);
		nOfDishes = viporders.getHead()->getItem().GetDishes();
		viporders.DeleteFirst();
		//Transfer the cook into the busy List
		busyCooks.insertSortedBusyCooks(vipcookslist.getHead()->getItem(), nOfDishes);
		vipcookslist.DeleteFirst();
	}
	//Check Normal Cooks for VIP orders
	while (normalcookslist.getCount() > 0 && viporders.getHead() != nullptr)
	{
		//get Cook ID 
		cookID = normalcookslist.getHead()->getItem().GetID();
		//set cook ID and type
		viporders.getHead()->getItem().setCookID(cookID);
		viporders.getHead()->getItem().setCookType(TYPE_NRM);
		//Add the order to inservice List and delete from the initial list
		speed = normalcookslist.getHead()->getItem().getSpeed();
		inserviceList.insertSortedInserviceOrders(viporders.getHead()->getItem(), speed);
		nOfDishes = viporders.getHead()->getItem().GetDishes();
		viporders.DeleteFirst();
		//Transfer the cook into the busy List
		busyCooks.insertSortedBusyCooks(normalcookslist.getHead()->getItem(), nOfDishes);
		normalcookslist.DeleteFirst();
	}
	//Check Vegan Cooks for VIP orders
	while (normalcookslist.getCount() > 0 && viporders.getHead() != nullptr)
	{
		//get Cook ID 
		cookID = vegancookslist.getHead()->getItem().GetID();
		//set cook ID and Type
		viporders.getHead()->getItem().setCookID(cookID);
		viporders.getHead()->getItem().setCookType(TYPE_VEG);
		//Add the order to inservice List
		speed = vegancookslist.getHead()->getItem().getSpeed();
		inserviceList.insertSortedInserviceOrders(viporders.getHead()->getItem(), speed);
		nOfDishes = viporders.getHead()->getItem().GetDishes();
		viporders.DeleteFirst();
		//Transfer the cook into the busy List
		busyCooks.insertSortedBusyCooks(vegancookslist.getHead()->getItem(), nOfDishes);
		vegancookslist.DeleteFirst();
	}
	
}

void Restaurant::assignNormalOrders()
{
	int cookID, speed, nOfDishes;
	while (normalorders.getCount() > 0 && normalcookslist.getCount() > 0)
	{
		//get Cook Id
		cookID = normalcookslist.getHead()->getItem().GetID();
		//set cookID and Type
		normalorders.getHead()->getItem().setCookID(cookID);
		normalorders.getHead()->getItem().setCookType(TYPE_VIP);
		//unlist the normal order and add it to the inservice list
		speed = normalcookslist.getHead()->getItem().getSpeed();
		nOfDishes = normalorders.getHead()->getItem().GetDishes();
		inserviceList.insertSortedInserviceOrders(normalorders.getHead()->getItem(), speed);
		normalorders.DeleteFirst();
		//unlist the cook and add it to the busy cooks
		busyCooks.insertSortedBusyCooks(normalcookslist.getHead()->getItem(), nOfDishes);
		normalcookslist.DeleteFirst();
	}
	while (normalorders.getCount() > 0 && normalcookslist.getCount() > 0)
	{	
		//get Cook Id
		cookID = vipcookslist.getHead()->getItem().GetID();
		//set cookID and Type
		normalorders.getHead()->getItem().setCookID(cookID);
		normalorders.getHead()->getItem().setCookType(TYPE_VIP);
		//unlist the normal order and add it to the inservice list
		speed = vipcookslist.getHead()->getItem().getSpeed();
		nOfDishes = normalorders.getHead()->getItem().GetDishes();
		inserviceList.insertSortedInserviceOrders(normalorders.getHead()->getItem(), speed);
		normalorders.DeleteFirst();
		//unlist the cook and add it to the busy cooks
		busyCooks.insertSortedBusyCooks(vipcookslist.getHead()->getItem(), nOfDishes);
		vipcookslist.DeleteFirst();
		
	}
}

void Restaurant::assignVeganOrders()
{
	int cookID, cookSpeed, nOfDishes;
	Order newOrder;

	if (vegancookslist.getCount() == 0 || veganorders.count() == 0)
		return;
	while (veganorders.count() > 0)
	{
		//check if vegan cooks are free
		if (vegancookslist.getCount() == 0) return;
		cookID = vegancookslist.getHead()->getItem().GetID();
		cookSpeed = vegancookslist.getHead()->getItem().getSpeed();
		//dequeue the first veganorder
		veganorders.dequeue(newOrder);
		nOfDishes = newOrder.GetDishes();
		//set cook ID and type
		newOrder.setCookID(cookID);
		newOrder.setCookType(TYPE_VEG);
		//insert the order into the inservicelist
		inserviceList.insertSortedInserviceOrders(newOrder, cookSpeed);
		//insert the cook into busy cooks list
		busyCooks.insertSortedBusyCooks(vegancookslist.getHead()->getItem(), nOfDishes);
		//delete the cook from its initial list
		vegancookslist.DeleteFirst();
	}
}

//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current time
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}


Restaurant::~Restaurant()
{
	
		delete pGUI;
}


void Restaurant::FillDrawingList()
{
	//draw  waiting order list
	int numOfVeganOrders = veganorders.count();
	Order vOrder;
	for (int i = 0; i<numOfVeganOrders;i++)
	{ 
		veganorders.dequeue(vOrder);
	    pGUI->addGUIDrawable(new VeganGUIElement(vOrder.GetID(), GUI_REGION::ORD_REG));
	    veganorders.enqueue(vOrder);

	}
	int numOfNormalOrders = normalorders.getCount();
	Order nOrder;
	for (int i = 0; i < numOfNormalOrders; i++)
	{
		nOrder = normalorders.getkth(i);
		pGUI->addGUIDrawable(new NormalGUIElement(nOrder.GetID(), GUI_REGION::ORD_REG));
	}
	int numOfVIPOrders = viporders.getCount(); //m7tagen n7otohm mtrtben 3lshan nshl 3la nfsna el rsm 
	Order vipOrder;
	for (int i = 0; i < numOfVIPOrders; i++)
	{
		vipOrder = viporders.getkth(i);
		pGUI->addGUIDrawable(new VIPGUIElement(vipOrder.GetID(), GUI_REGION::ORD_REG));
	}
	//Drawing Available cooks list
	int numOfveganCooks = vegancookslist.getCount();
	Cook veganCook;
	for (int i = 0; i < numOfveganCooks; i++)
	{
		veganCook = vegancookslist.getkth(i);
		if (veganCook.getState() == 0)
		{
			pGUI->addGUIDrawable(new VeganGUIElement(veganCook.GetID(), GUI_REGION::COOK_REG));
		}
	}
	int numOfnormalCooks = normalcookslist.getCount();
	Cook normalCook;
	for (int i = 0; i < numOfnormalCooks; i++)
	{
		normalCook = normalcookslist.getkth(i);
		if (normalCook.getState() == 0)
		{
			pGUI->addGUIDrawable(new NormalGUIElement(normalCook.GetID(), GUI_REGION::COOK_REG));
		}
	}
	int numOfvipCooks = vipcookslist.getCount();
	Cook vipCook;
	for (int i = 0; i < numOfvipCooks; i++)
	{
		vipCook = vipcookslist.getkth(i);
		if (vipCook.getState() == 0)
		{
			pGUI->addGUIDrawable(new VIPGUIElement(vipCook.GetID(), GUI_REGION::COOK_REG));
		}
	}
	//Drawing in service orders list
	Order inServiceOrder;
	int numOfInServiceOrder = inserviceList.getCount();
	for (int i = 0; i < numOfInServiceOrder; i++)
	{
		inServiceOrder = inserviceList.getkth(i);
		if (inServiceOrder.GetType() == TYPE_VEG)
		{
			pGUI->addGUIDrawable(new VeganGUIElement(inServiceOrder.GetID(), GUI_REGION::SRV_REG));
		}
		else if (inServiceOrder.GetType() == TYPE_VIP)
		{
			pGUI->addGUIDrawable(new VIPGUIElement(inServiceOrder.GetID(), GUI_REGION::SRV_REG));
		}
		else if (inServiceOrder.GetType() == TYPE_NRM)
		{
			pGUI->addGUIDrawable(new NormalGUIElement(inServiceOrder.GetID(), GUI_REGION::SRV_REG));
		}
		
	}

	//Drawing Finished orders
	Order finishedOrder;
	for (int i = 0; i < numOfFinishedOrders; i++)
	{
		finishedOrder = Finished_Orders[i];
		if (finishedOrder.GetType() == TYPE_VEG)
		{
			pGUI->addGUIDrawable(new VeganGUIElement(finishedOrder.GetID(), GUI_REGION::DONE_REG));
		}
		else if (finishedOrder.GetType() == TYPE_VIP)
		{
			pGUI->addGUIDrawable(new VIPGUIElement(finishedOrder.GetID(), GUI_REGION::DONE_REG));
		}
		else if (finishedOrder.GetType() == TYPE_NRM)
		{
			pGUI->addGUIDrawable(new NormalGUIElement(finishedOrder.GetID(), GUI_REGION::DONE_REG));
		}
	}
}



void Restaurant::load_from_file(string filename)
{   //open file
	ifstream infile;
	infile.open(filename.c_str());

	//checking for opening failure:
	if (!infile) {
		cerr << "\n Unable to open files \n ";
		exit(1);   // call system to stop
	}
  //counting the lines
	int number_of_lines = 0;
	std::string LINE;
	while (getline(infile, LINE))
		++number_of_lines;

	// returning to the beginning of the file
	infile.clear();
	infile.seekg(0, ios::beg);

	// storing each line as a string element in an array of strings
	string* lines = new string[number_of_lines];
	int i = 0;
	while (!infile.eof())
	{
		getline(infile, lines[i], '\n');
		i++;
	}

	// retrieving speed, #of cooks,... and other onformation from thr first 5 lines of the file (before events)
	int SV, SN, SG, ncooks_n, ncooks_vip, ncooks_veg, bm, bn, bv, bg, n_autopromote, m;

	 stringstream snorm(lines[0].substr(0, 1));
	 stringstream sveg(lines[0].substr(2, 1));
	 stringstream svip(lines[0].substr(4, 1));
	 snorm >> SN;
	 sveg >> SG;
	 svip >> SV;
	 stringstream cn(lines[1].substr(0, 1));
	 stringstream cg(lines[1].substr(2, 1));
	 stringstream cv(lines[1].substr(4, 1));
	 cn >> ncooks_n;
	 cg >> ncooks_veg;
	 cv >> ncooks_vip;

	 stringstream a(lines[2].substr(0, 1));
	 stringstream b(lines[2].substr(2, 1));
	 stringstream c(lines[2].substr(4, 1));
	 stringstream d(lines[2].substr(6, 1));
	 a >> bm;
	 b >> bn;
	 c >> bg;
	 d >> bv;

	 stringstream e(lines[3]);
	 e >> n_autopromote;
	 stringstream o(lines[4]);
	 o >> m;

	 totl_num_cooks = ncooks_n + ncooks_veg + ncooks_vip;
	  
	 //populating cooks lists
	 //convention, normal cooks ids will usually be in the 10s, veg will be in the 50s, and vip will be in the 100s
	 for (int i = 0; i < ncooks_n;i++)
	 { 
		 Cook x (i, TYPE_NRM, SN, bn,bm);
			 normalcookslist.InsertEnd(x);
	 }
	 

	 for (int i = 0; i < ncooks_veg; i++)
	 {
		 Cook x(i+50, TYPE_VEG, SG, bg,bm);
		 vegancookslist.InsertEnd(x);
	 }

	
	 for (int i = 0; i < ncooks_vip; i++)
	 {
		 Cook x(i + 100, TYPE_VIP, SV, bv,bm);
		 vipcookslist.InsertEnd(x);
	 }
	 
	 

	 // populating orders & event lists and queues
	 string ev_type; int a_t, i_d, n_dish; double cost, prom_cost; ORD_TYPE O_t;

	 int n_orders = 0; //leh byzed fe 7eta wa7da bs?
	 for (int i = 5; i < m+5; i++)  

	 { 
		 ev_type = lines[i].substr(0, 1); //event type
	 stringstream tt(lines[i].substr(2, 1));  
		 tt >> a_t;  //arrival timestep

		 //order arrival events 
	    if (ev_type=="R"){
			//record id
			stringstream tt1(lines[i].substr(6, 1));
			tt1 >> i_d;
			//record #of dishes
			stringstream tt2(lines[i].substr(8, 1));
			tt2 >> n_dish;
			//record order cost
			stringstream tt3(lines[i].substr(10, 1));
			tt3 >> cost;
			//store order,as per type
			string Oo_t = lines[i].substr(4, 1);
			if (Oo_t == "N") {
				O_t = TYPE_NRM;
				//Order OOn(i_d, O_t);
				//normalorders.InsertEnd(OOn);
				//n_orders++;
			}

			else if (Oo_t == "V")
			{
				O_t = TYPE_VIP;
				//Order OOv(i_d, O_t);
				//viporders.InsertSorted(OOv);

				//Order OOv(i_d, O_t);
				//viporders.InsertEnd(OOv);



			}
			else
			{
				O_t = TYPE_VEG;
				//Order OOg(i_d, O_t);
				//veganorders.enqueue(OOg);
			}
			Event* evv = new ArrivalEvent(a_t, i_d, O_t, n_dish, cost);

			EventsQueue.enqueue(evv);
		}


		//enquiuing the cancellation events in event queue 

		else if (ev_type == "X"){
			int id_canc; 
			stringstream iddd(lines[i].substr(4, 1));
			iddd >> id_canc;
			Event* evv2 = new cancellationEvent(a_t, id_canc);

			EventsQueue.enqueue(evv2);
		}

		//enquiuing the promotion events in event queue
		else {
			int id_prom; double ex_mon;
			stringstream iddd(lines[i].substr(4, 1));
			iddd >> id_prom;
			stringstream mon(lines[i].substr(6, 1));
			mon >> ex_mon;
			Event* evv3 = new promotionEvent(a_t, id_prom,ex_mon);

			EventsQueue.enqueue(evv3);
		}
		 
	 }
	 int vbvvmn = EventsQueue.count();
	
}
//change sizeof to numOffinishedorders
/*void Restaurant::save_to_file(string filename)
{
	ofstream outfile;
	outfile.open(filename.c_str(), ios::out | ios::trunc);

	//checking for opening failure:
	if (!outfile) {
		cerr << "\n Unable to open files \n ";
		exit(1);   // call system to stop
	}

	int v_co = vipcookslist.getCount(), g_co = vegancookslist.getCount(), n_co = normalcookslist.getCount();
	int n_ord = sizeof(Finished_Orders);
	int n_co = totl_num_cooks;
	int n_ord = totl_num_orders;
	Order O;
	int sumwait = 0, wait;
	outfile << "FT  ID  AT  W  ST" << "\n";
	int sumserv, serv;
	for (int i = 0; i < sizeof(Finished_Orders); i++) {
		for (int i = 0; i < totl_num_orders; i++) {

			O = Finished_Orders[i];
			wait = O.GetFinish() - O.getAT();
			sumwait += wait;
			serv = O.getST();
			sumserv += serv;
			outfile << O.GetID() << "\t\t" << O.GetFinish() << "\t\t" << O.GetID() << "\t\t" << O.getAT() << "\t\t" << wait << "\t\t" << serv << "\t\t";

			outfile << "\n";

		}
		outfile << "...............................\n";
		outfile << "orders   :  " << n_ord << "   norm:  " << normalorders.getCount() << "   vip:  " << viporders.getCount() << "   vegan:  " << veganorders.count();
		outfile << "\n cooks:  " << v_co + n_co + g_co << "  norm:  " << n_co << "  veg:  " << g_co << "  vip:  " << v_co;
		outfile << "\n cooks:  " << n_co << "  norm:  " << normalcookslist.getCount() << "  veg:  " << vegancookslist.getCount() << "  vip:  " << vipcookslist.getCount();
		outfile << "\navg wait:   " << double(sumwait) / n_ord << "  avg serv:   " << double(sumserv) / n_ord;
		outfile << "\n autopromoted : " << n_autopromoted;

	}
}*/

	LinkedList<Order> Restaurant::getNormalOrders()
	{
		return normalorders;
	}

	LinkedList<Order> Restaurant::getVipOrders()
{
	return viporders;
}

Queue<Order> Restaurant::getVeganOrders()
{
	return veganorders;
}

LinkedList<Cook> Restaurant::getVipCookList()
{
	return vipcookslist;
}

LinkedList<Cook> Restaurant::getVeganCookList()
{
	return vegancookslist;
}


LinkedList<Cook> Restaurant::getNormalCookList()
{
	return normalcookslist;
}

Order* Restaurant::getFinishedOrders()
{
	return Finished_Orders;
}



void Restaurant::moveToFinished()
{
	int veganflag = 0;
	int vipflag = 0;
	int normalflag = 0;
	int veganID, vipID, normalID;
	ORD_TYPE type;
	int count = inserviceList.getCount();
	for (int i = 0; i < count; i++)
	{
		type = inserviceList.getkth(i).GetType();
		if (type == TYPE_VEG && veganflag == 0)
		{
			Finished_Orders[numOfFinishedOrders] = inserviceList.getkth(i);
			numOfFinishedOrders++;
			veganID = inserviceList.getkth(i).GetID();
			veganflag = 1;
		}
		else if (type == TYPE_VIP && vipflag == 0)
		{
			Finished_Orders[numOfFinishedOrders] = inserviceList.getkth(i);
			numOfFinishedOrders++;
			vipID = inserviceList.getkth(i).GetID();
			vipflag = 1;
		}
		else if (type == TYPE_NRM && normalflag == 0)
		{
			Finished_Orders[numOfFinishedOrders] = inserviceList.getkth(i);
			numOfFinishedOrders++;
			normalID = inserviceList.getkth(i).GetID();
			normalflag = 1;
		}
		if (normalflag == 1 && vipflag == 1 && veganflag == 1)
		{
			break;
		}
	}
	if (veganflag == 1)
	{
		inserviceList.DelNode(veganID);
	}
	if (normalflag == 1)
	{
		inserviceList.DelNode(normalID);
	}
	if (vipflag == 1)
	{
		inserviceList.DelNode(vipID);
	}
}

void Restaurant::pickOneOrder()
{
	if (viporders.getCount() > 0) {
		Order vipOrder = viporders.getkth(0); 
		viporders.DeleteFirst();
		inserviceList.InsertEnd(vipOrder);
	}
	if (normalorders.getCount() > 0) {
		Order normalOrder = normalorders.getkth(0); 
		normalorders.DeleteFirst();
		inserviceList.InsertEnd(normalOrder);
	}
	if (veganorders.count() > 0) {
		Order veganOrder;
		veganorders.dequeue(veganOrder);
		inserviceList.InsertEnd(veganOrder);
	}
}







bool Restaurant::EventsQueueIsEmpty()
{ // this function checks if the Event Queue is empty or not
	return EventsQueue.isEmpty();
}

