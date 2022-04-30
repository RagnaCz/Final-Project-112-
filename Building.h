#include <iostream>
#include <iomanip>
using namespace std;
#ifndef BUILDING_H
#define BUILDING_H

class Building{
    int area, power_use, garbage;
protected:
    string name;
    int quantity, last_power, last_garbage;
public:
		Building(string n, int q, int a, int p, int g){
			name = n;       quantity = q;  area = a;
      power_use = p;  garbage = g;   last_power= last_garbage= 0;
		}
		virtual ~Building(){}
    int use_power()  { return power_use*quantity; }
    int get_garbage(){ return garbage*quantity;   }
		void add_qty(int rand){ quantity += rand; }
		int get_area(){ return area; }

		virtual void show_status(int&,int&);
    void set_lastp(int p){ last_power += p; }
    void reset_lastp(){ last_power=0; }
    virtual void set_lastgarbage(int g){ last_garbage += g; }
    virtual void reset_lastgarbage(){ last_garbage=0; }
};

class School: public Building{
    int wkr;
public:
		School(string n,int q,int a,int p,int g): Building(n,q,a,p,g),wkr(0){}
    ~School(){}
    void show_status(int&,int&);
		int getqty()     { return quantity; }
    int make_worker(){
      wkr = (rand()%80+41)*quantity;
      return wkr;
    }
};

class University: public Building{
    int eng;
public:
		University(string n,int q,int a,int p,int g): Building(n,q,a,p,g),eng(0){}
    ~University(){}
    void show_status(int&,int&);
		int getqty()        { return quantity; }
    int make_engineer(){
      eng = (rand()%70+31)*quantity;
      return eng;
    }
};

class Farm: public Building{
    static int manure;
public:
		Farm(string n,int q,int a,int p,int g):Building(n,q,a,p,g){}
    ~Farm(){}
    static int take_manure(int);
    void show_status(int&,int&);
    void make_manure(){ manure += quantity*400*((rand()%(125-75+1))+75)/100; }
    void decompose(){
      manure -= quantity*400*((rand()%41)+80)/100;
      if(manure<0) manure=0;
    }
};

class Waste_plant: public Building{
    static int garbage;
    int last_destroy;
public:
		Waste_plant(string n,int q,int a,int p,int g):Building(n,q,a,p,g),last_destroy(0){}
    ~Waste_plant(){}
    static int take_garbage(int);
    void show_status(int&,int&);
    void destroy_garbage();
    void collect_garbage(int grb){ garbage += grb; }
    void reset_lastgarbage(){ last_destroy=0; }
};

/*
Village
school
Market
waste plant
Hotel
Mall
Airport
Harbor
  */
#endif

