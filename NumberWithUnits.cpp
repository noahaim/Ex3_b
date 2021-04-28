#include "NumberWithUnits.hpp"
#include <fstream>
// #include <iostream>
// #include <sstream>
// #include <stdexcept> 
using namespace ariel;
using namespace std;

std::map<std::string ,std::map<std::string,double>> NumberWithUnits::AllUnits;

namespace ariel{
    const float EPS =0.0001;
    NumberWithUnits::NumberWithUnits(double num,const std::string &u)
    {    //check that unit that we get is in the map AllUnits
        if(AllUnits.find(u)!=AllUnits.end()){
            number=num;
            unit=u;
        }
        else{ throw std::invalid_argument("no legal unit");}
    }
    void NumberWithUnits::read_units(std::ifstream& f)
    {
        std::string unit1,unit2,equal;
        double num1=0,num2=0;
        //get line from the file  
        while(f>>num1>>unit1>>equal>>num2>>unit2) 
        {
            NumberWithUnits::AllUnits[unit1][unit2]=num2;//add unit 2 to unit 1
            NumberWithUnits::AllUnits[unit2][unit1]=1/num2;//add unit 1 to unit 2

            std::map<std::string,double>::iterator it;
            //Go through the list of all the units that have a ratio to unit1 and add their ratio to unit2 
            for(it=AllUnits[unit1].begin();it!=AllUnits[unit1].end();it++)
            {
                if(it->first!=unit2){
                    AllUnits[it->first][unit2]=AllUnits[it->first][unit1]*num2;
                    AllUnits[unit2][it->first]=1/AllUnits[it->first][unit2];
                }
            }
            //Go through the list of all the units that have a ratio to unit2 and add their ratio to unit1 
            for(it=AllUnits[unit2].begin();it!=AllUnits[unit2].end();it++)
            {
                if(it->first!=unit1){
                    AllUnits[it->first][unit1]=AllUnits[unit2][unit1]*AllUnits[it->first][unit2];
                    AllUnits[unit1][it->first]=1/AllUnits[it->first][unit1];
                }
            }
        }
            f.close();
        }
        NumberWithUnits operator+(const NumberWithUnits& n1,const NumberWithUnits& n2){
            //if n1 and n2 have the same unit
            if(n1.unit==n2.unit)
            {
                return  NumberWithUnits(n1.number+n2.number,n1.unit);
            }
            //if n1 and n2 not have the samee unit but we have ratio between them
            if(NumberWithUnits::AllUnits[n2.unit][n1.unit]!=0.0)
            {
                return NumberWithUnits(n1.number+n2.number*NumberWithUnits::AllUnits[n2.unit][n1.unit],n1.unit);
            }
            throw invalid_argument("Units do not match - ["+n1.unit+"] cannot be converted to ["+n2.unit+"]");
        }
        NumberWithUnits operator-(const NumberWithUnits& n1,const NumberWithUnits& n2){
            return n1+(-n2);
        }
        NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits& other){
            //if this and other have the same unit
            if(this->unit==other.unit)
            {
                this->number+=other.number;
                return *this;
            }
            //not have the same unit but there is ratio between them
            if(NumberWithUnits::AllUnits[this->unit][other.unit]!=0)
            {
                this->number+=other.number*NumberWithUnits::AllUnits[other.unit][this->unit];
                return *this;
            }
            throw invalid_argument("Units do not match - ["+this->unit+"] cannot be converted to ["+other.unit+"]");
        }
        NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& other){
            return *this+=(-other);
       }
        NumberWithUnits NumberWithUnits::operator+()const{
            return NumberWithUnits(this->number,this->unit);
        }
        NumberWithUnits NumberWithUnits::operator-()const{
            return NumberWithUnits(-(this->number),this->unit);
        }
        bool operator<(const NumberWithUnits& n1, const NumberWithUnits& n2)
        {
            //if they have the same unit
            if(n1.unit==n2.unit)
            {
                return (n2.number-n1.number>EPS);
            }
            //not have the same unit but have ratio between them
            if(NumberWithUnits::AllUnits[n2.unit][n1.unit]!=0)
            {
                return (NumberWithUnits::AllUnits[n2.unit][n1.unit]*n2.number-n1.number>EPS);
            }
            throw invalid_argument("Units do not match - ["+n1.unit+"] cannot be converted to ["+n2.unit+"]");
        }
        bool operator<=(const NumberWithUnits& n1, const NumberWithUnits& n2)
        {
            return (n1<n2||n1==n2);
        }
        bool operator>(const NumberWithUnits& n1, const NumberWithUnits& n2)
        {
            return (n2<n1);
        }
        bool operator>=(const NumberWithUnits& n1, const NumberWithUnits& n2)
        {
            return (n1==n2||n1>n2);
        }
        bool operator==(const NumberWithUnits& n1, const NumberWithUnits& n2)
        {
            //have the same unit
            if(n1.unit==n2.unit)
            {
                return (abs(n1.number-n2.number)<EPS);
            }
            //not have the same unit but there is ratio between them
            if(NumberWithUnits::AllUnits[n2.unit][n1.unit]!=0)
            {
                return (abs(NumberWithUnits::AllUnits[n2.unit][n1.unit]*n2.number-n1.number)<EPS);
            }
            throw invalid_argument("Units do not match - ["+n1.unit+"] cannot be converted to ["+n2.unit+"]");
        }
        bool operator!=(const NumberWithUnits& n1, const NumberWithUnits& n2)
        {
            return !(n1==n2);
        }
        //++a
        NumberWithUnits& NumberWithUnits::operator++()
        {
            this->number++;
            return *this;
        }
        //a++
        NumberWithUnits NumberWithUnits::operator++(int dummy_flag_for_postfix_increment)
        {   
            NumberWithUnits copy=*this;
            this->number++;
            return copy;
        }  
        //--a
        NumberWithUnits& NumberWithUnits::operator--()
        {
            this->number--;
            return *this;
        }
        //a--
        NumberWithUnits NumberWithUnits::operator--(int dummy_flag_for_postfix_increment)
        {
            NumberWithUnits copy=*this;
            this->number--;
            return copy;
        }
        //operator * between NumberWithUnit and double
        NumberWithUnits operator* (const NumberWithUnits& n,double d)
        {
            return NumberWithUnits(n.number*d,n.unit);
        }
        //operator * between double and NumberWithUnit
        NumberWithUnits operator* (double d,const NumberWithUnits& n)
        {
            return NumberWithUnits(n.number*d,n.unit);
        }
        std::ostream& operator<< (std::ostream& os, const NumberWithUnits& n)
        {
            return os<<n.number<<"["<<n.unit<<"]";
        }
        std::istream& operator>> (std::istream& is, NumberWithUnits& n)
        {
            char c=0;
            double num=0;
            string s_unit;
            is>>num>>c>>s_unit;
            //if in s_unit there is ] in the last char
            if(s_unit.at(s_unit.length()-1)==']')
            {
                s_unit=s_unit.substr(0,s_unit.length()-1);
            }
            //s_unit not have the char ] because there was " " after the string of the unit
            else{is>>c;} 
            //check that the unit is in the map
            if(NumberWithUnits::AllUnits.find(s_unit)!=NumberWithUnits::AllUnits.end())
            {
                n.number=num;
                n.unit=s_unit;
                return is;
            }
            throw std::invalid_argument("no legal"); //the unit not in the map
        }
}