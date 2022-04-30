#include <iostream>
#include <iomanip>
#include "ANSI-color-codes.h"
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
using namespace std;
#include "Player.h"
#include "Power.h"

void Player::short_status(int power_in,int power_out,int eng,int wkr){
  gotoxy(6,4);  cout<<"Name  : "<< name;
	gotoxy(6,5);	cout<<"Power : "<< back_up <<" (+"<< power_in <<"/-"<< power_out <<")";
  gotoxy(6,6);  cout<<"Money : "<< money <<" (+"<< power_out*4 <<")";
  gotoxy(37,4);	cout<<"Time     : "<< year <<" years "<< month <<" months";
	gotoxy(37,5);	cout<<"Engineer : " << engineer <<" (+"<< eng <<")";
	gotoxy(37,6); cout<<"Worker   : " << worker<<" (+"<< wkr <<")";
}

void Player::information(){
	gotoxy(7,14);
	  cout<<BLK<<WHTB<<" Information "<<reset<<reset;
	gotoxy(8,15);
	  cout<<"Area       : "<<Player::all_area<<" km2";
	gotoxy(8,16);
		cout<<"Wave zone  : "<<Player::wave_zone<<" km";
	gotoxy(8,17);
		cout<<"Fossil fuel: "<<Player::fuel<<" litres";
	gotoxy(40,15);
		cout<<"Used area : "<<Player::unavail_area<<" km2";
	gotoxy(40,16);
		cout<<"Number of rivers : "<<Player::river;
	gotoxy(40,17);
		cout<<"Coal zone : "<<Player::coal<<" kg";
}

void lose(){cout<<""<<endl;
cout<<"######################################"<<endl;
cout<<"      _      ____   _____ ______"<<endl;
cout<<"     | |    / __ \\ / ____|  ____|"<<endl;
cout<<"     | |   | |  | | (___ | |__"<<endl;
cout<<"     | |   | |  | |\\___ \\|  __|"<<endl;
cout<<"     | |___| |__| |____) | |____"<<endl;
cout<<"     |______\\____/|_____/|______|"<<endl<<endl;
cout<<"######################################"<<endl;
cout<<"      Press any key to continue";
}

void win(){cout<<""<<endl;
cout<<"#####################################"<<endl;
cout<<"     __          _______ _   _ "<<endl;
cout<<"     \\ \\        / /_   _| \\ | |"<<endl;
cout<<"      \\ \\  /\\  / /  | | |  \\| |"<<endl;
cout<<"       \\ \\/  \\/ /   | | | . ` |"<<endl;
cout<<"        \\  /\\  /   _| |_| |\\  |"<<endl;
cout<<"         \\/  \\/   |_____|_| \\_|"<<endl<<endl;
cout<<"#####################################"<<endl;
cout<<"      Press any key to continue";
}

int Player::update(int pin,int pout,int max_backup,int eng,int wkr){
  if(pout-pin>=back_up){
    back_up=0;
    if(system("clear"));
    lose();
		return 0;
  }else if(all_area<=unavail_area){
		if(system("clear"));
		win();
		return 0;
	}else{
    if(back_up+pin-pout>=max_backup) back_up = max_backup;
    else back_up = back_up+pin-pout;
    money += pout*4;
    engineer += eng;
    worker += wkr;
		return 1;
  }
}

int Player::take_fuel(int ptt_qty){
  if(ptt_qty==-1) return fuel;
  int fl=(rand()%11+95)*250*ptt_qty/100;
  if(fuel<fl){
    fl = fuel;
    fuel = 0;
  }
  else fuel -= fl;
  return fl;
}

int Player::take_coal(int cl_qty){
  if(cl_qty==-1) return coal;
  int cl=(rand()%11+95)*800*cl_qty/100;
  if(coal<cl){
    cl = coal;
    coal = 0;
  }
  else coal -= cl;
  return cl;
}

Player::Player(string n, int area,int uarea){
  name = n;       money = 35000;   back_up = 25000;
  engineer = worker = 75;
  year= month= turn = 0;
  all_area = area;         unavail_area = uarea;
  wave_zone = area/350;    river = area/25000+rand()%5;
  fuel = area*6/5;         coal = area*13/10;
}

int Player::all_area =0 ;     int Player::unavail_area =0 ;
int Player::wave_zone =0 ; int Player::fuel =0 ;
int Player::river =0 ;        int Player::coal =0 ;