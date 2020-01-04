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
	int cookID;
	ORD_TYPE cookType;
	double serviceTime;
	int autoS; //that represent the number of timesteps after which an order is automatically promoted to VIP
	//
	// TODO: Add More Data Members As Needed
	//

public:
	Order();
	Order(int ID, ORD_TYPE r_Type);
	Order(int arrivalTime,int ID, ORD_TYPE r_Type, int size, double money);

	virtual ~Order();

	int get_stept_bef_autopromote();
	void set_stept_bef_autopromote(int s);
	int GetID();

	ORD_TYPE GetType() const; //azon m7tagen settype 3lshan el promotion

	void SetDishes(int d);
	int GetDishes() const;

	void SetFinish(int d);
	int GetFinish() const;

	
	void setStatus(ORD_STATUS s); //order statues : wait, service, done
	ORD_STATUS getStatus() const;

	void setAT(int s); //arrivl time
	int getAT() const;

	void setST(int s); //servicetime
	int getST() const;

	void setMoney(double money); //total order money
	double getMoney() const;

	void setVIPpriority(int p); // VIP order Priority
	int getVIPpriority(); //go and give them definition
	
	double getPriority();

	int getCookID() const;
	void setCookID(int ID);

	ORD_TYPE getCookType() const;
	void setCookType(ORD_TYPE Type);

	double getServiceTime() const;
	void setServiceTime(double time);

	void setAutoS(int s);
	int getAutoS();
	//
	// TODO: Add More Member Functions As Needed
	//

};
