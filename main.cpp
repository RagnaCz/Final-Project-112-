#include <iostream>
#include <cstdlib>
#include <string.h>
#include <cstring>
#include <math.h>
#include <string>
#include "Building.h"
#include "Player.h"
#include "Power.h"
#include "GETCH.h"
#include "ANSI-color-codes.h"
#define ENTER '\n'
#define esc 27
#define up 65
#define down 66
#define right 67
#define left 68
//#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
using namespace std;

int mainmenu();
  void Pages(int);
Player start();
  inline void pic_powerplant();
void play(Player);
  int all_garbage(Building *building[10]);
  int generate_power(Power *power[10]);
  int use_power(Building *building[10]);

  void menu_bar(int);
  void powerplant_status(Power *powerPtr[10]);
  void building_status(Building *b[10]);
  void shop(int,Power *powerPtr[10],Player&);
    void newline(char chr[121],int x,int y,int max);

  void expanding(Building *b[10],int,Player&);
  bool check_keypress(char&,int&,int&,Player&,Power *power[10]);
void tutorial();
void credit();

int swing_num(int,int,int);
string spc(int,string=" ");
void rectangle(int,int,int);

class my_getch: public exception{
public:
    virtual const char* what() const throw() { 
      return "Please input number correctly.";
    }
};
class my_cin: public exception{
public:
    virtual const char* what() const throw() { 
      return "Please input name between 1-15 letters.";
    }
};

int main(){
  srand(time(0));
	while(mainmenu()){}
	if(system("clear"));
  cout<< "Goodbye!" <<endl;
  return 0;
}

int mainmenu(){
	my_getch Wrong_num_input;
	if(system("clear"));
  rectangle(29,11,50); pic_powerplant();
  gotoxy(49,4); cout<<BLK<<WHTB<<spc(6)<<"My Little Power Plant"<<spc(6)<<reset<<reset;
  gotoxy(59,5);cout<<"1. Play game";
  gotoxy(59,6);cout<<"2. Tutorial";
  gotoxy(59,7);cout<<"3. Credit";
  gotoxy(59,8);cout<<"4. Exit ";
  gotoxy(58,10);cout<<"Press a number";

  int c; char A[2]="1";
  do{
  	try{
  		A[0] = getch();
  		c = atoi(A);
  		if(c<1 || c>4) throw Wrong_num_input;
  	}
  	catch(exception &e){
  	  gotoxy(13,19);
  		cout<<e.what();
  	}	
  }while(c<1 || c>4);
  if(c==4) return 0;
  else if(c>0 && c<4) Pages(c);
  return 1;
}

void Pages(int a){
		if(system("clear"));
    switch(a){
			case 1: play(start()); break;
	    case 2: tutorial(); break;
	    case 3: credit(); break;
    }
}

Player start(){
  my_cin Wrong_str_input;
	my_getch Wrong_num_input;
	char name[30], chr[2]="1";
  int i,area,month=0,year=0;
	do{
    gotoxy(1,1); rectangle(35,17,10);
    gotoxy(9,4); cout<<BLK<<WHTB<<spc(11)<<"Create an account"<<spc(11)<<reset<<reset;
    gotoxy(20,6); cout<<"What's your name?";
    gotoxy(21,7); cout<<">>";
  	try{
  	  gotoxy(24,7); cin>>name;
  		if(strlen(name)<1 || strlen(name)>15) throw Wrong_str_input;
  	}
  	catch(exception &e){
  	  if(system("clear"));
			gotoxy(9,20);
  		cout<<e.what();
			cin.clear();
  		cin.ignore(10,'\n');
  	}
  }while(strlen(name)<1 || strlen(name)>15);
  gotoxy(1,20); cout<<spc(45);
  gotoxy(21,9); cout<<"Choose map size";
  gotoxy(23,10); cout<<"1. Small";
  gotoxy(23,11); cout<<"2. Medium";
  gotoxy(23,12); cout<<"3. Large";
  gotoxy(23,13); cout<<"4. Random";
  gotoxy(16,15); cout<<"Press a number to choose";
  do{
		try{
			chr[0] = getch();
	    i = atoi(chr);
			if(i<1 || i>4) throw Wrong_num_input;
		}
  	catch(exception &e){
  	  gotoxy(9,20);
  		cout<<e.what();
  	}
  }while(i<1||i>4);
  if(system("clear"));
  if(i==4) i = rand()%3+1;
  switch(i){
    case 1: area=30089;break;
    case 2: area=50077;break;
    case 3: area=100731;break;
  }
  area = swing_num(area,95,105);
  Player person(name,area,30+10+4+2+3+10);
  return person;
}

void play(Player person){
	//name, power, quantity, contruction, area, sci, wkr, cost
  Incineration incineration("Incineration",650,0,6,3,150,200,30000); 
  Biogas       biogas            ("Biogas",1000,0,7,30,150,300,45000);
  Powerhouse   powerhouse    ("Powerhouse",0,3,4,10,100,130,12000);
  Dam          Dam                  ("Dam",2200,0,10,200,225,250,50000);
	Coal         Coal          ("Coal-fired",2400,0,18,5,275,350,70000);
  Tidal        Tidal              ("Tidal",750,0,8,40,150,150,40000);
	Petroleum    Petroleum    ("Fossil fuel",2750,0,21,5,250,400,75000);
	Power       				 windturbine("Wind turbine",290,1,4,10,50,75,12500),
              		 Solar_cell("Solar cell",330,0,4,20,75,125,15000),
             					   Nuclear("Nuclear",3500,0,27,15,400,450,100000);
	Power *powerPtr[10]={&powerhouse, &windturbine, &Solar_cell, &incineration, &Tidal,
      &biogas, &Dam, &Coal, &Petroleum, &Nuclear};
	//name, quantity, area, power_use, garbage
  University  university("University",1,4,200,35);   School school("School",1,2,100,30);
  Waste_plant waste_plant("Waste plant",1,3,150,0);  Farm   farm("Farm",0,40,80,10);
  Building    Village("Village",2,5,200,80),  Market("Market",0,1,70,40),
              Hotel("Hotel",0,3,350,60),      Mall("Mall",0,4,400,60),
              Airport("Airport",0,35,300,60), Harbor("Habor",0,10,150,50);
  Building *buildingPtr[10] = {&Village, &school, &Market, &waste_plant, &university,
      &Hotel, &farm, &Mall, &Airport, &Harbor};
  char chr='g';
  int i,j, page=1, vline=1, power_in=0, power_out=0, eng=0, wkr=0;
  
  while(chr!=esc){
		do{
      gotoxy(1,1); rectangle(70,8,0);
	    person.short_status(power_in,power_out,eng,wkr);
      gotoxy(1,11); rectangle(70,24,0);
	    switch(page){
	      case 1: person.information(); powerplant_status(powerPtr); break;
	      case 2: building_status(buildingPtr); break;
	      case 3: shop(vline,powerPtr,person); break;
	      case 4:
	        gotoxy(25,21);cout<<"press \'Y\' to exit";
	        gotoxy(24,23);cout<<"press \'N\' to cancel";
	        break;
	    }
	    gotoxy(1,10); menu_bar(page);
	    gotoxy(23,33); cout<<"  press \'E\' to end turn";
	    do{
				  chr = getch();
	    }while(check_keypress(chr,page,vline,person,powerPtr));
		}while(chr!='e'&&chr!='E'&&chr!=esc);
    if(system("clear"));
    
		for(i=0;i<10;i++) powerPtr[i]->reset_lastpower();
    for(i=0;i<10;i++){
      buildingPtr[i]->reset_lastp();
      buildingPtr[i]->reset_lastgarbage();
    }
    for(power_in=0, power_out=0, eng=0, wkr=0, i=0; i<4; i++){//Algorithm
      waste_plant.collect_garbage(all_garbage(buildingPtr));
      farm.make_manure();
      power_in += generate_power(powerPtr);
      power_out += use_power(buildingPtr);
      waste_plant.destroy_garbage();
      farm.decompose();
      wkr = school.make_worker();
      eng = university.make_engineer();
      for(j=0;j<10;j++) powerPtr[j]->decrese_time();//time_left--
    }
		if(person.update(power_in,power_out,powerhouse.max_backup(),eng,wkr)==0){
			getch();
			break;
		}
	  person.add_time();
		expanding(buildingPtr,person.getturn(),person);
    page = 1;
  }
  if(system("clear"));
}

void powerplant_status(Power *powerPtr[10]){
    gotoxy(7,19);
	  cout<<BLK<<WHTB<<"    Power plant                Quantity         Power     "<<reset<<reset;
    int i, sumpwr=0;
    for(i = 0;i<10;i++){
        gotoxy(9,20+i);
        powerPtr[i]->show_status(sumpwr);
    }
    gotoxy(11,31); cout<<"Total"<<setfill('_')<<setw(44)<< sumpwr <<setfill(' ');
}

void building_status(Building *b[10]){
  int i, a=16, sumpwr=0, sumgrb=0;
  gotoxy(5,a-2);
  cout<<BLK<<WHTB<<"  Building          Quantity   Use power   Garbage    Other  "<<reset<<reset;
  for(i=0;i<10;i++){
    gotoxy(6,a+i);
    b[i]->show_status(sumpwr,sumgrb);
  }
  gotoxy(10,28); cout<<"Total"<<setfill('_')<<setw(28)<< sumpwr <<setw(10)<< sumgrb <<setfill(' ');
}

void shop(int vline,Power *powerPtr[10],Player &person){
  gotoxy(6,14);
  cout<<BLK<<WHTB<<"    Name          Cost  Power   Time  Eng  Wkr     status   "<<reset<<reset;
	for(int i=0;i<10;i++){
    gotoxy(3,16+i);
		if(vline==i+1) cout<<">> ";
		else cout<<"   ";
		powerPtr[i]->sell_data(person);
		if(vline==i+1) cout<<" <<"<<endl;
	}

	char Descript[10][151]{
		"A place where can be stored energy. Built to increase the limit of energy storage, but unable to produce energy.",
		"Wind turbines can receive and transform kinetic energy from wind movement into mechanical energy. to be used to generate power.",
    "Solar cell is an electrical device that converts the energy of light directly into electricity by the photovoltaic effect",
    "Incineration is a waste treatment process that involves the combustion of substances contained in waste materials.",
    "Tidal is harnessed by converting energy from tides into useful forms of power, mainly electricity using various methods.",
    "Biogas is a mixture of gases, produced from raw materials such as manure It is a renewable energy source.",
    "Dam is a form of renewable energy that uses the power of moving water to generate electricity.",
    "Coal is a nonrenewable fossil fuel that is combusted and used to generate electricity.",
    "Petroleum, sometimes known as crude oil, is a kind of fossil fuel. It is a non-renewable energy source that is used to generate power.",
    "Nuclear power is the use of nuclear reactions to produce electricity."
	};
  
  gotoxy(6,27);
	cout<<BLK<<WHTB<<"  Description  "<<reset<<reset<<" : ";
	cout<<powerPtr[vline-1]->get_name();
	gotoxy(7,28);
	cout<<" ";
	int i=0,k=0,l=0,m=0;
	for(i=0;i<=strlen(Descript[vline-1]);i++){
		cout<<Descript[vline-1][i];
		k++;
		if(l>0) m = 55; else m = 54; 
		if(k>=m&&Descript[vline-1][i]==' '){
			l++;
			gotoxy(6,28+l);
			k=0;
		}
	}
}

bool check_keypress(char &chr, int &page,int &vline, Player &p, Power *power[10]){
  if(page==4){
    switch(chr){
      case 'y': case 'Y': chr=esc;
      case 'n': case 'N': page=1; return false;
    }
  }
  switch(chr){
    case left:
        if(page>1) page--;
        else {page=1; return true;}
        vline=1;
        break;
    case right:
        if(page<4) page++;
        else {page=4; return true;}
        vline=1;
        break;
    case up:
        if(page==3&&vline>1) vline--;
        else {vline=1; return true;}
        break;
    case down:
        if(page==3&&vline<10) vline++;
        else {vline=10; return true;}
        break;
    case ENTER:
        if(page==3) if(power[vline-1]->check_status()){
          gotoxy(20,33);cout<<"press enter again to confirm";
          char a; a = getch();
          gotoxy(20,33);cout<<spc(28);
          if(a == ENTER){
            power[vline-1]->set_status(2);
            int c,s,w,a;
            power[vline-1]->buy(c,s,w,a);
            p.pay(c,s,w,a);
            return false;
          }
        }
          // check status
          // 2nd enter
          // change status&count time
          // pay money
        return true;
		case 'e': case 'E': break;
    default: return true;
  }
  return false;
}

int all_garbage(Building *building[10]){//no waste_plant3
  int garbage=0, g=0, i,j=0;
  for(i=0;i<10;i++){
    if(i!=3){
      g = swing_num(building[i]->get_garbage(),80,120);
      building[i]->set_lastgarbage(g);
      garbage += g;
    }
  }
  return garbage;
}

int generate_power(Power *power[10]){//incineration3,biogas5,Coal7,Petroleum8
    int power_in=0, p=0,i;
    for(i=1;i<10;i++){
      p = swing_num(power[i]->get_power(),80,120);
      power[i]->set_pout(p);
      power_in += p;
    }
    return power_in;
}

int use_power(Building *building[10]){
  int power_out=0, p=0,i;
  for(i=0;i<10;i++){
    p = swing_num(building[i]->use_power(),85,125);
    building[i]->set_lastp(p);
    power_out += p;
  }
  return power_out;
}

void menu_bar(int page){
  int i,j;
  cout<<spc(6+(page-1)*13)<<"   ____________"<<spc((4-page)*13)<<endl;
  cout<<"        |   Status   |  Building  |    Shop    |    Exit    |           "<<endl;
  cout<<"--------";
  for(i=1;i<=page;i++){
    if(i==page) cout<<"-            ";
    else cout<<"-------------";
  }
	for(i=1;i<=4-page;i++){
		cout<<"-------------";
	}
	cout<<"----------";
}

void tutorial(){
gotoxy(1,2);
	rectangle(53,25,1);
	gotoxy(1,1);
	rectangle(14,4,0);
	gotoxy(2,3);
	cout<<"  Tutorial  "<<endl;
	gotoxy(5,6);cout<<"Hello, you will be the new Power plant manager!";
	gotoxy(5,7);cout<<"You might be a little confuse when start game.";
	gotoxy(5,9);cout<<"When you start, you will have....";
	gotoxy(5,10);cout<<"Powerhouse   x 3 for store energy.";
	gotoxy(5,11);cout<<"Wind turbine x 1 for produce energy.";
	gotoxy(5,13);cout<<"And remember....";
	gotoxy(5,14);cout<<"School will produce worker,";
	gotoxy(5,15);cout<<"University will produce engineer.";
	gotoxy(1,16);
	rectangle(20,4,4);gotoxy(2,16);cout<<"|";gotoxy(2,17);cout<<"|";
	gotoxy(2,18);cout<<"|";gotoxy(2,19);cout<<"|";
	gotoxy(7,18);cout<<"Wining condition";
	gotoxy(26,18);cout<<": Area of your map is full.";
	gotoxy(1,20);
	rectangle(20,4,4);gotoxy(2,20);cout<<"|";gotoxy(2,21);cout<<"|";
	gotoxy(2,22);cout<<"|";gotoxy(2,23);cout<<"|";
	gotoxy(7,22);cout<<"Losing condition";
	gotoxy(26,22);cout<<": Energy not enough.";
	gotoxy(5,25);
	cout<<"Press any key to continue. Good luck have fun !"<<endl;
	getch();
}

void credit(){
  cout<<spc(12)<<"_______________________________"<<endl;
  cout<<spc(11)<<"/"<<spc(31)<<"\\"<<endl;
  cout<<spc(10)<<"|"<<spc(33)<<"|"<<endl;
  cout<<spc(8)<<BLK<<WHTB<<spc(16)<<"Credits"<<spc(16)<<reset<<reset<<endl;
  cout<<spc(10)<<"|"<<spc(33)<<"|"<<endl;
  cout<<spc(10)<<"|"<<spc(6)<<"\"N'Nate and the gang\""<<spc(6)<<"|"<<endl;
  cout<<spc(10)<<"|"<<spc(33)<<"|"<<endl;
  cout<<spc(10)<<"|"<<spc(4)<<"6013132 Ai Kengsurakarn  "<<spc(4)<<"|"<<endl;
  cout<<spc(10)<<"|"<<spc(4)<<"6413106 Ploypailin       "<<spc(4)<<"|"<<endl;
  cout<<spc(10)<<"|"<<spc(4)<<"6413215 Tanawat Kanchan  "<<spc(4)<<"|"<<endl;
  cout<<spc(10)<<"|"<<spc(4)<<"6413220 Natedee Mueankrut"<<spc(4)<<"|"<<endl;
  cout<<spc(10)<<"|"<<spc(33)<<"|"<<endl;
	cout<<spc(10)<<"|"<<spc(4)<<"Press any key to continue"<<spc(4)<<"|"<<endl;
  cout<<spc(10)<<"|"<<spc(33)<<"|"<<endl;
  cout<<spc(11)<<"\\_______________________________/"<<endl;
	getch();
}

void pic_powerplant(){
gotoxy(1,6);
cout<<"          ) ) )                     ) ) )"<<endl;
cout<<"        ( ( (                      ( ( ("<<endl;
cout<<"      ) ) )                       ) ) )"<<endl;
cout<<"   (~~~~~~~~~)                 (~~~~~~~~~)"<<endl;
cout<<"    | POWER |                   | POWER |"<<endl;
cout<<"    |       |                   |       |"<<endl;
cout<<"    I      _._                  I       _._"<<endl;
cout<<"    I    /'   `\\                I     /'   `\\"<<endl;
cout<<"    I   |   N   |               I    |   N   |"<<endl;
cout<<"    f   |   |~~~~~~~~~~~~~~|    f    |    |~~~~~~~~~~~~~~|"<<endl;
cout<<"  .'    |   ||~~~~~~~~|    |  .'     |    | |~~~~~~~~|   |"<<endl;
cout<<"/'______|___||__###___|____|/'_______|____|_|__###___|___|"<<endl;
}
int swing_num(int base,int least,int max){
  if(base==0) return 0;
  int i=(rand()%(max-least+1))+least;
  return base*i/100;
}
string spc(int qty,string spam){
  string str=""; int i;
  for(i=0;i<qty;i++) str=str+spam;
  return str;
}
void rectangle(int w,int h,int t){
  int i,j;
  for(i=0;i<h;i++){
    cout<<spc(t);
    switch(i){
      case 0:cout<<" "<<spc(w-2,"_")<<endl; break;
      case 1:cout<<"/"<<spc(w-2)<<"\\"<<endl; break;
      default:
        if(i==h-1) cout<<"\\"<<spc(w-2,"_")<<"/"<<endl;
        else cout<<"|"<<spc(w-2)<<"|"<<endl;
    }
  }
}

void expanding(Building *building[10],int turn,Player &person){
  /*float chance=1.1*sqrt(turn-10)+30;
  if(turn<=10) chance=30;
  if(swing_num(100,0,100)<=chance){
    building[0]->add_qty(1);
    person.add_area(building[0]->get_area(),1);
  }
  if(turn>4){
    
  }
  if(turn>10){
    
  }*/
  
	int add_temp;
	int base[10]={2,1,1,1,1,1,1,1,1,1};
	for(int i=0;i<3;i++){
		add_temp = base[i]*sqrt(turn);
		add_temp = swing_num(add_temp,10,60);
		building[i]->add_qty(add_temp);
    person.add_area(building[i]->get_area(),add_temp);
	}
	if(turn>=4){
	for(int i=3;i<7;i++){
		add_temp = base[i]*sqrt(turn);
		add_temp = swing_num(add_temp,10,50);
		building[i]->add_qty(add_temp);
		person.add_area(building[i]->get_area(),add_temp);
	}}
	if(turn>=8){
	for(int i=7;i<10;i++){
		add_temp = base[i]*sqrt(turn);
		add_temp = swing_num(add_temp,10,40);
		building[i]->add_qty(add_temp);
		person.add_area(building[i]->get_area(),add_temp);
	}}
}