#include <iostream>
using namespace std;
#include "Building.h"

void Building::show_status(int &sumpwr,int &sumgrb){
  cout<<left<<setw(13)<< name;
  cout<<right<<setw(11)<< quantity;
  cout<<setw(13)<< last_power;
  cout<<setw(10)<< last_garbage;
  sumpwr+=last_power;
  sumgrb+=last_garbage;
}

void School::show_status(int &sumpwr,int &sumgrb){
  cout<<left<<setw(13)<< name;
  cout<<right<<setw(11)<< quantity;
  cout<<setw(13)<< last_power;
  cout<<setw(10)<< last_garbage;
  cout<<"     Wkr +"<< wkr;
  sumpwr+=last_power;
  sumgrb+=last_garbage;
}

void University::show_status(int &sumpwr,int &sumgrb){
  cout<<left<<setw(13)<< name;
  cout<<right<<setw(11)<< quantity;
  cout<<setw(13)<< last_power;
  cout<<setw(10)<< last_garbage;
  cout<<"     Eng +"<< eng;
  sumpwr+=last_power;
  sumgrb+=last_garbage;
}

void Farm::show_status(int &sumpwr,int &sumgrb){
  cout<<left<<setw(13)<< name;
  cout<<right<<setw(11)<< quantity;
  cout<<setw(13)<< last_power;
  cout<<setw(10)<< last_garbage;
  cout<<setw(11)<< manure;
  printf("\033[%d;%dH",(22),(10)); cout<<"(manure)";
  sumpwr+=last_power;
  sumgrb+=last_garbage;
}

void Waste_plant::show_status(int &sumpwr,int &sumgrb){
  cout<<left<<setw(13)<< name;
  cout<<right<<setw(11)<< quantity;
  cout<<setw(13)<< last_power;
  cout<<setw(10)<< last_destroy*(-1);
  cout<<setw(11)<< garbage;
  sumpwr+=last_power;
  sumgrb-=last_destroy;
}

int Farm::take_manure(int bio_qty){
  int mnr=(rand()%11+95)*100*bio_qty/100;
  if(manure<mnr){
    mnr = manure;
    manure = 0;
  }
  else manure -= mnr;
  return mnr;
}

void Waste_plant::destroy_garbage(){
    int g = quantity*100*((rand()%41)+60)/100;
    if(g>garbage) g=garbage;
    garbage -= g;
    last_destroy += g;
}

int Waste_plant::take_garbage(int incin_qty){
    int garb=(rand()%11+95)*130*incin_qty/100;
    if(garbage<garb){
      garb = garbage;
      garbage = 0;
    }
    else garbage -= garb;
    return garb;
}

int Farm::manure = 0;
int Waste_plant::garbage = 0;