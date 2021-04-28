#include <string>
#include <map>
namespace ariel{
class NumberWithUnits{
    double number;
    std::string  unit;
    static std::map<std::string ,std::map<std::string,double>> AllUnits;

    public:
        NumberWithUnits(double num,const std::string &u);
        static void read_units(std::ifstream& f);

        friend NumberWithUnits operator+(const NumberWithUnits& n1,const NumberWithUnits& n2);
        NumberWithUnits& operator+=(const NumberWithUnits& other);
        NumberWithUnits operator+() const;

        friend NumberWithUnits operator-(const NumberWithUnits& n1,const NumberWithUnits& n2);
        NumberWithUnits& operator-=(const NumberWithUnits& other);
        NumberWithUnits operator-() const;

        friend bool operator<(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator<=(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator>(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator>=(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator==(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator!=(const NumberWithUnits& n1, const NumberWithUnits& n2);

        NumberWithUnits& operator++();//++a
        NumberWithUnits operator++(int dummy_flag_for_postfix_increment);//a++
        NumberWithUnits& operator--();//--a
        NumberWithUnits operator--(int dummy_flag_for_postfix_increment);//a--

        friend NumberWithUnits operator*(const NumberWithUnits& n,double d);
        friend NumberWithUnits operator*(double d,const NumberWithUnits& n);

        friend std::ostream& operator<< (std::ostream& os, const NumberWithUnits& n);
        friend std::istream& operator>> (std::istream& is, NumberWithUnits& n);

    };
}