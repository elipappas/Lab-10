#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <sstream>
using namespace std;
#ifndef TEST_H
#define TEST_H
using namespace std;
struct node {
    string name;
    double resistance;
    double voltage_across;
    double power_across;
};
class Ohms{
  private:
      vector <node> resistors;
      double voltage;
      double current;
  public:
      Ohms();
      Ohms(double);
      void setVoltage(double);
      bool setOneResistance(string, double);
      double getVoltage(); 
      double getCurrent(); 
      vector <node> getNode();
      double sumResist();
      bool calcCurrent();
      bool calcVoltageAcross();
      bool calcPowerAcross();
      double calcTotalPower();
      string displayTotal();
      bool seriesConnect(Ohms);
      bool seriesConnect(vector <Ohms> & );
      void operator= (Ohms);
      bool operator< (Ohms); 
};
#endif

Ohms::Ohms(){     //This is the default constructor
  voltage = 0;
}
Ohms::Ohms(double volt){
  voltage = volt;
}
void Ohms::setVoltage(double volt) {
   voltage = volt;
}
bool Ohms::setOneResistance(string name, double resistance) {
   if (resistance <= 0) {
      return false;
   }
   node n;
   n.name = name;
   n.resistance = resistance;
   resistors.push_back(n);
   return true;
}

double Ohms::getVoltage(){
   return voltage;
}

double Ohms::getCurrent(){
   return current;
}

vector<node> Ohms::getNode() {
   return resistors;
}

double Ohms::sumResist(){
   double total = 0;
   for(int i = 0; i < resistors.size(); i++){
      total += resistors[i].resistance;
   }
   return total;
}

bool Ohms::calcCurrent() {
   if(voltage <= 0 || resistors.size() == 0) {
         return false;
   }
   current = voltage/sumResist();
   return true;
}

bool Ohms::calcVoltageAcross(){
   if(voltage <= 0 || resistors.size() == 0){
      return false;
   }

      double voltAcross = 0;
      for(int i = 0; i < resistors.size(); i++){
         voltAcross += resistors[i].voltage_across;
      }
      return true;

}

bool Ohms::calcPowerAcross(){
   if(voltage <= 0 || resistors.size() == 0){
      return false;
   }

      double powerAcross = 0;
      for(int i = 0; i < resistors.size(); i++){
         powerAcross += resistors[i].power_across;
      }
      return true;
}

double Ohms::calcTotalPower() {
   calcCurrent();
   return voltage*current;
}

string Ohms::displayTotal(){
   for(int i = 0; i < resistors.size(); i++){
      cout << "Resistors Name: " << resistors[i].name << ", Resistance: " << resistors[i].resistance << ", Voltage Across: " << resistors[i].voltage_across << ", Power Across: " << resistors[i].power_across << endl;
   }
}

bool Ohms::seriesConnect(Ohms ohms) {
   if(ohms.getNode().size() == 0){
      return false;
   }
   else {
      vector<node> temp = ohms.getNode();
      for (int i = 0; i < temp.size(); i++){
         this->resistors.push_back(temp[i]);
      }
      return true;
   }
}

bool Ohms::seriesConnect(vector<Ohms>&ohms){
   if(ohms.size() == 0){
      return false;
   }
   else {
      for (int i = 0; i < ohms.size(); i++){
         this->seriesConnect(ohms[i]);
      }
      return true;
   }
}

bool Ohms::operator<(Ohms ohms) {
   if(ohms.getNode().size() == 0){
      return false;
   }
   if(this->sumResist() < ohms.sumResist()){
      return true;
   }
   return false;
}


int main(){
   Ohms ckt1(100);
   int i = 0;
   string name;
   double resistance;
   while(i<3){
      cout << "enter resistor name: ";
      cin >> name;
      cout << "enter resistance of circuit: ";
      cin >> resistance;
      ckt1.setOneResistance(name,resistance);
      cin.ignore();
      i++;
   }
   cout << "Total power consumption = " << ckt1.calcTotalPower() << endl;
   return 0;
}
