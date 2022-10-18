#include <iostream>
#include <cstdint>

#ifndef _FRACTION_H
#define _FRACTION_H

class Fraction {
    private:
        int32_t
            num,
            den;

    public:
        Fraction(int _num = 0, int _den = 1);
        ~Fraction() = default;

        // rhs == right hand side, as in the right hand side of an operator
        Fraction operator+(Fraction rhs);
        Fraction operator-(Fraction rhs);
        Fraction operator*(Fraction rhs);
        Fraction operator/(Fraction rhs);
        Fraction &operator=(Fraction rhs);

        bool operator==(Fraction rhs);
        bool operator!=(Fraction rhs);
        bool operator<=(Fraction rhs);
        bool operator>=(Fraction rhs);
        bool operator>(Fraction rhs);
        bool operator<(Fraction rhs);

        int32_t getNum() { return num; }
        int32_t getDen() { return den; }
};

std::istream &operator>>(std::istream &is, Fraction &f);
std::ostream &operator<<(std::ostream &os, Fraction f);

#endif
