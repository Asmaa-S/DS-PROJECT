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

	while (!this->EventsQueueIsEmpty()|| !veganorders.isEmpty() || normalorders.getCount() !=0 || viporders.getCount() !=0) //ba2y 2zwd el in service list
	{	//excute current time step events
		ExecuteEvents(step);
		//pick one order

		//c.	Each 5 timesteps, move an order of each type from In-service list(s) to finished list(s)

		//update interface
		this->FillDrawingList(); 
		pGUI->updateInterface();
		pGUI->printStringInStatusBar("Current Time: " + std::to_string(step)+ "/n"+"  No Of Vegan Waiting orders: " + std::to_string(veganorders.count()) + "  No Of Normal Waiting orders: " + std::to_string(normalorders.getCount()) + "  No Of VIP Waiting orders: " + std::to_string(viporders.getCount())+"/n" +"  No Of Available Vegan Cooks: " + std::to_string(vegancookslist.getCount()) + "  No Of Available Normal Cooks: " + std::to_string(normalcookslist.getCount()) + "  No Of Available VIP Cooks: " + std::to_string(vipcookslist.getCount()));
		pGUI->updateInterface();
		pGUI->handleSimGUIEvents();
		pGUI->waitForClick();
		step++; //increase time by one
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
	//This function should be implemented in phase1
	//It should add ALL orders and cooks to the drawing list
	//It should get orders from orders lists/queues/stacks/whatever (same for cooks)
	//how to draw cooks?

	//draw order list

	//draw  waiting order list
	int numOfVeganOrders = veganorders.count;
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

	//Drawing Finished orders

	int numOfFinishedOrders = sizeof(Finished_Orders);
	Order finishedOrder;
	for (int i = 0; i < numOfFinishedOrders; i++)
	{
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
		 Cook x (i, TYPE_NRM, SN, bn);
			 normalcookslist.InsertEnd(x);
	 }
	 

	 for (int i = 0; i < ncooks_veg; i++)
	 {
		 Cook x(i+50, TYPE_VEG, SG, bg);
		 vegancookslist.InsertEnd(x);
	 }

	
	 for (int i = 0; i < ncooks_vip; i++)
	 {
		 Cook x(i + 100, TYPE_VIP, SV, bv);
		 vipcookslist.InsertEnd(x);
	 }
	 
	 

	 // populating orders & event lists and queues
	 string ev_type; int a_t, i_d, n_dish; double cost, prom_cost; ORD_TYPE O_t;

	 int n_orders;
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
				n_orders++;
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
				Order OOg(i_d, O_t);
				veganorders.enqueue(OOg);
			}
			Event* evv = new ArrivalEvent(a_t, i_d, O_t);

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
	// int vbvvmn = EventsQueue.count();
	
}
void Restaurant::save_to_file(string filename)
{
	ofstream outfile; 
	outfile.open(filename.c_str(), ios::out | ios::trunc);

	//checking for opening failure:
	if (!outfile) {
		cerr << "\n Unable to open files \n ";
		exit(1);   // call system to stop
	}

	int v_co= vipcookslist.getCount(), g_co=vegancookslist.getCount(), n_co= normalcookslist.getCount();
	int n_ord = sizeof(Finished_Orders);
	int n_co= totl_num_cooks;
	int n_ord = totl_num_orders;
	Order O;
	int sumwait = 0, wait;
	outfile << "FT  ID  AT  W  ST" << "\n";
	int sumserv,serv;
	for (int i = 0; i < sizeof(Finished_Orders); i++) {
	for (int i = 0; i < totl_num_orders; i++) {
		
		O= Finished_Orders[i];
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


Order* Restaurant::getFinishedOrders()
{
	return Finished_Orders;
}


Order* Restaurant::getInserviceList()
{
	return &inserviceList;
}

void Restaurant::moveToFinished()
{
	int x =0;
	int f = 0;
	ORD_TYPE finished[3];
	for (int i = 0; i < sizeof(inserviceList); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (inserviceList[i].getType() == Finished_Orders[j])
				f = 1;

		}
		if (f == 1) break;
		Finished_Orders[size(Finished_Orders) - 1] = inserviceList[i];
	}
	if (x == 3) break;

}

void Restaurant::pickOneOrder()
{
	Node<Order> *headvip =viporders.getHead();
	inserviceList[inservice] = headvip->getItem();
	viporders.DeleteFirst();
	inservice++;
	Node<Order> *headnormal = normalorders.getHead();
	inserviceList[inservice] = headnormal->getItem();
	normalorders.DeleteFirst();
	inservice++;
	Node<Order> *headvegan = veganorders.peekFront();
	Order headvegan;
	veganorders.dequeue(headvegan);
	

}







bool Restaurant::EventsQueueIsEmpty()
{ // this function checks if the Event Queue is empty or not
	return EventsQueue.isEmpty();
}

