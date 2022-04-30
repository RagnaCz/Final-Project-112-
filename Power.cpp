#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdlib.h>
#include "Power.h"
#include "ANSI-color-codes.h"
using namespace std;

void Power::sell_data(Player &person){
  int sta=1;
  int a = 5;
	cout<<left<<setw(12)<< name <<right;
  
	if(person.getmoney()<cost){
    cout<<RED<<setw(5+a)<<cost<<reset;
    sta=0;
  }
  else cout<<setw(5+a)<<cost;
  
	cout<<setw(7)<<power;
  
	int m,y;
	y = construction/12;
	m = construction%12;
  if(y==0) cout<<"    ";
  else cout<<setw(3)<< y <<"y";
  cout<<setw(2)<< m <<"m";
  
	if(person.geteng()<engineer_rqm){
    cout<<RED<<setw(5)<< engineer_rqm <<reset;
    sta=0;
  }
	else cout<<setw(5)<< engineer_rqm;
  
	if(person.getwkr()<worker_rqm){
    cout<<RED<<setw(5)<< worker_rqm <<reset;
    sta=0;
  }
  else cout<<setw(5)<<worker_rqm;

  switch(status){
    case 0: if(sta==1) status=1; break;
    case 1: if(sta==0) status=0; break;
  }
  switch(status){
    case 0: cout<<"    Disabled  "; break;
    case 1: cout<<"      BUY     "; break;
    case 2: cout<<"  Constructing"; break;
    case 3: cout<<"      Max     "; break;
  }
}

void Power::set_status(int num){
  status = num;
  if(num==2) time_left = construction;
  /*if(num==4){
    if(time_left>0){
      time_left--;
      if(time_left==0){
        status=1;
        quantity++;
      }
    }
    else if(status==2){
      status=1;
      quantity++;
    }
  }*/
}

void Power::show_status(int &sumpwr){
  cout<<left<<setw(13)<< name;
  cout<<right<<setw(22)<< quantity;
  cout<<setw(16)<< last_power;
  sumpwr+=last_power;
}

void Powerhouse::show_status(int &sumpwr){
  cout<<left<<setw(13)<< name;
  cout<<right<<setw(22)<< quantity;
  cout<<setw(16)<< back_up*quantity;
  gotoxy(20,20); cout<<"(back up)";
}

void Dam::show_status(int &sumpwr){
  cout<<left<<setw(13)<< name;
  cout<<right<<setw(22)<< quantity;
  cout<<setw(16)<< last_power;
  gotoxy(44,26);cout<<"/"<< Player::get_river();
  sumpwr+=last_power;
}

void Tidal::show_status(int &sumpwr){
  cout<<left<<setw(13)<< name;
  cout<<right<<setw(22)<< quantity;
  cout<<setw(16)<< last_power;
  gotoxy(44,24);cout<<"/"<< Player::get_beach()/20;
  sumpwr+=last_power;
}

void Coal::show_status(int &sumpwr){
  cout<<left<<setw(13)<< name;
  cout<<right<<setw(22)<< quantity;
  cout<<setw(16)<< last_power;
  gotoxy(44,27);cout<<"/"<< max_qty;
  sumpwr+=last_power;
}

void Petroleum::show_status(int &sumpwr){
  cout<<left<<setw(13)<< name;
  cout<<right<<setw(22)<< quantity;
  cout<<setw(16)<< last_power;
  gotoxy(44,28);cout<<"/"<< max_qty;
  sumpwr+=last_power;
}

//********************************************

bool Power::check_status(){
  gotoxy(19,33); cout<<"                              ";
  switch(status){
    case 0: gotoxy(19,33);cout<<RED<<"Cannot buy. Read the red text."<<reset; break;
    case 1: return true;
    case 2: gotoxy(28,33);cout<<RED<<"Constructing!"<<reset; break;
  }
  return false;
}

bool Dam::check_status(){
  if(Player::get_river()<=quantity) status=3;
  gotoxy(19,33); cout<<"                              ";
  switch(status){
    case 0: gotoxy(19,33);cout<<RED<<"Cannot buy. Read the red text."<<reset; break;
    case 1: return true;
    case 2: gotoxy(28,33);cout<<RED<<"Constructing!"<<reset; break;
    case 3: 
      gotoxy(19,33);
      cout<< name <<" max quantity: "<< quantity <<"/"<< Player::get_river(); break;
  }
  return false;
}

bool Tidal::check_status(){
  if(Player::get_beach()/20<=quantity) status=3;
  gotoxy(19,33); cout<<"                              ";
    switch(status){
      case 0: gotoxy(19,33);cout<<RED<<"Cannot buy. Read the red text."<<reset; break;
      case 1: return true;
      case 2: gotoxy(28,33);cout<<RED<<"Constructing!"<<reset; break;
      case 3: 
        gotoxy(19,33);
        cout<< name <<" max quantity: "<< quantity <<"/"<< Player::get_beach()/20; break;
    }
  return false;
}

bool Coal::check_status(){
  if(max_qty<=quantity) status=3;
  gotoxy(19,33); cout<<"                              ";
  switch(status){
    case 0: gotoxy(19,33);cout<<RED<<"Cannot buy. Read the red text."<<reset; break;
    case 1: return true;
    case 2: gotoxy(28,33);cout<<RED<<"Constructing!"<<reset; break;
    case 3: 
      gotoxy(19,33);
      cout<< name <<" max quantity: "<< quantity <<"/"<< max_qty; break;
  }
  return false;
}

bool Petroleum::check_status(){
  if(max_qty<=quantity) status=3;
  gotoxy(19,33); cout<<"                              ";
  switch(status){
    case 0: gotoxy(19,33);cout<<RED<<"Cannot buy. Read the red text."<<reset; break;
    case 1: return true;
    case 2: gotoxy(28,33);cout<<RED<<"Constructing!"<<reset; break;
    case 3: 
      gotoxy(19,33);
      cout<< name <<" max quantity: "<< quantity <<"/"<< max_qty; break;
  }
  return false;
}

Power::Power(string n, int p, int q, int c, int a, int eng, int wkr, int co){
    name = n; power = p;   quantity = q;
    construction = c;      area_rqm = a;
    engineer_rqm = eng;   worker_rqm = wkr;
    cost = co;             status = 1;
    time_left = 0;         last_power = 0;
}