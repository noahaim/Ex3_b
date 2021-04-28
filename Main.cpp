#include <iostream>
#include <fstream>
// #include <sstream>
// #include <stdexcept>
 using namespace std;
#include "NumberWithUnits.hpp"
using namespace ariel;

int main() {
  ofstream Myunits_file;
  Myunits_file.open("Myunits_file.txt");
  Myunits_file<<"1 km = 1000 m"<<endl;
  Myunits_file<<"1 m = 100 cm"<<endl;
  Myunits_file<<"1 year = 12 month"<<endl;
  Myunits_file<<"1 day = 24 hour"<<endl;
  Myunits_file<<"1 hour = 60 min"<<endl;
  Myunits_file<<"1 min = 60 sec"<<endl;
  Myunits_file.close();
  ifstream units_file{"Myunits_file.txt"};
  NumberWithUnits::read_units(units_file);

  cout<<"Enter 2 NumberWithUnits:"<<endl;
  NumberWithUnits num1(1,"day");
  NumberWithUnits num2(1,"day");
  try{
    cin>>num1>>num2;
    cout<<num1<<"+"<<num2<<"="<<num1+num2<<endl;
    cout<<num1<<"-"<<num2<<"="<<num1-num2<<endl;
    cout<<num1<<"+="<<num2<<"="<<(num1+=num2)<<endl;
    cout<<num1<<"-="<<num2<<"="<<(num1-=num2)<<endl;
    cout<<num1<<"*"<<"2"<<"="<<(num1*2)<<endl;
    cout<<"2"<<"*"<<num1<<"="<<(2*num1)<<endl;
    cout<<"-"<<num2<<"="<<(-num2)<<endl;
    cout<<"+"<<num1<<"="<<(+num1)<<endl;
    cout<<num1<<"++"<<"="<<(num1++)<<endl;
    cout<<num1<<"--"<<"="<<(num1--)<<endl;
    cout<<"++"<<num1<<"="<<(++num1)<<endl;
    cout<<"--"<<num1<<"="<<(--num1)<<endl;

  }
  catch (const std::exception& ex) {
    cout << ex.what() << endl;
}
}
