#pragma once

#include "..\Defs.h"

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, Vegan, VIP
	ORD_STATUS status;	//waiting, in-service, done
	int Dishes;	//The number of dishes in that order 
	int vip_priority;
	double totalMoney;	//Total order money
	int steps_bef_autopromote;
	int ArrTime, ServTime, FinishTime;	//arrival, service start, and finish times
	
	//
	// TODO: Add More Data Members As Needed
	//

public:
	Order();
	Order(int ID, ORD_TYPE r_Type);
	virtual ~Order();

	int get_stept_bef_autopromote();
	void set_stept_bef_autopromote(int s);
	int GetID();

	ORD_TYPE GetType() const;

	void SetDishes(int d);
	int GetDishes() const;

	void SetFinish(int d);
	int GetFinish() const;

	
	void setStatus(ORD_STATUS s);
	ORD_STATUS getStatus() const;
	void setAT(int s); //arrivl time
	int getAT() const;

	void setST(int s); //servicetime
	int getST() const;
	
	double getPriority();
	//
	// TODO: Add More Member Functions As Needed
	//

};
