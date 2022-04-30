#include <iostream>
#include <iomanip>
#include "Building.h"
using namespace std;
#ifndef PLAYER_H
#define PLAYER_H

class Player{
    string name;
    int money, back_up;
    int engineer, worker;
    int year,month,turn;
    //Geography
    static int all_area, unavail_area;
    static int wave_zone, fuel;
    static int river, coal;
public:
    Player(string,int,int);
    ~Player(){}
    void short_status(int,int,int,int);
    void information();
    static int take_fuel(int);
    static int take_coal(int);
    int update(int,int,int,int,int);
		void add_area(int area_rqm,int qty){
			unavail_area += area_rqm * qty;
		}

    void pay(int cost,int eng,int wkr,int area){
      money -= cost;
      engineer -= eng;
      worker -= wkr;
      unavail_area += area;
    }
    void add_time(){
			turn++;
			month = (turn*4)%12;
			year = (turn*4)/12;
		}
    static int get_river(){ return river; }
    static int get_beach(){ return wave_zone; }
		int getturn()  { return turn; }
		int getmonth() { return month; }
		int getyear()  { return year; }
		int getmoney() { return money; }
		int getwkr()   { return worker; }
		int geteng()   { return engineer; }
};

#endif
