#include <string>
#include "Player.h"
using namespace std;
#ifndef POWER_H
#define POWER_H
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

class Power{
    int power, cost;
    int construction, area_rqm;
    int engineer_rqm, worker_rqm, time_left;
protected:
    string name;
    int quantity, last_power;
    int status;
public:
    Power(string,int,int,int,int,int,int,int);
		virtual ~Power(){}
    virtual bool check_status();
    virtual void show_status(int&);
		void sell_data(Player&);
		int getarea(){ return area_rqm;	}

    virtual int get_power(){ return power*quantity; }
    
		void buy(int &c,int &s,int &w,int &a){
      c = cost;
      s = engineer_rqm;
      w = worker_rqm;
      a = area_rqm;
    }
		int get_qty()     { return quantity; }
		string get_name() { return name; }
    void set_status(int num);
    void decrese_time(){
      if(time_left>0){
        time_left--;
        if(time_left==0){
          status=1;
          quantity++;
        }
      }
    }
    void set_pout(int p){ last_power+=p; }
    void reset_lastpower(){ last_power=0; }
};

class Powerhouse: public Power{
    int back_up;
public:
    Powerhouse(string n,int p,int q,int c,int a,int eng,int wkr,int co): Power(n,p,q,c,a,eng,wkr,co), back_up(10000){}
		~Powerhouse(){}
    int max_backup(){ return back_up*quantity; }
    void show_status(int&);
};

class Biogas: public Power{
public:
    Biogas(string n,int p,int q,int c,int a,int eng,int wkr,int co): Power(n,p,q,c,a,eng,wkr,co){}
    ~Biogas(){}
    int get_power(){ return (Farm::take_manure(quantity))*10; }
};

class Incineration: public Power{
public:
    Incineration(string n,int p,int q,int c,int a,int eng,int wkr,int co): Power(n,p,q,c,a,eng,wkr,co){}
    ~Incineration(){}
    int get_power(){ return (Waste_plant::take_garbage(quantity))*5; }
};

class Dam: public Power{
public:
		Dam(string n,int p,int q,int c,int a,int eng,int wkr,int co): Power(n,p,q,c,a,eng,wkr,co){}
		~Dam(){}
    bool check_status();
    void show_status(int&);
};

class Tidal: public Power{
public:
		Tidal(string n,int p,int q,int c,int a,int eng,int wkr,int co): Power(n,p,q,c,a,eng,wkr,co){}
		~Tidal(){}
    bool check_status();
    void show_status(int&);
};

class Coal: public Power{
    unsigned int max_qty;
public:
		Coal(string n,int p,int q,int c,int a,int eng,int wkr,int co): Power(n,p,q,c,a,eng,wkr,co){
      max_qty = Player::take_coal(-1)/8000;
    }
		~Coal(){}
    int get_power(){ return (Player::take_coal(quantity))*3; }
    bool check_status();
    void show_status(int&);
};

class Petroleum: public Power{
    unsigned int max_qty;
public:
		Petroleum(string n,int p,int q,int c,int a,int eng,int wkr,int co): Power(n,p,q,c,a,eng,wkr,co){
      max_qty = Player::take_fuel(-1)/9500;
    }
		~Petroleum(){}
    bool check_status();
    void show_status(int&);
    int get_power(){ return (Player::take_fuel(quantity))*11; }
};

#endif

/*
Mill
Solar_cell
Coal
Dam
Tide
Petroleum 
Nuclear
*/