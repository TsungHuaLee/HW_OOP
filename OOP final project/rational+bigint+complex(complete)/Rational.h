//  Project - Rational.h(interface)
//
//  Team No.14(蘇辰堯、張育碩、李宗樺)
//  Name:張育碩
//  StudentID:404410047
//  Dept:CSIE
//  Year:2
//

#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <string>
#include "BigInt.h"
using std::istream;
using std::ostream;
using namespace bigint;

namespace rational
{
    class Rational
    {
    public:
        Rational();
        Rational(BigInt num, BigInt deno);
        Rational(BigInt wholeNumber);
        Rational(const Rational &iniObj);

        Rational& operator =(const Rational &rside);

        friend ostream& operator <<(ostream& output, const Rational &n);
        friend istream& operator >>(istream& input, Rational &n);
        friend const Rational operator *(const Rational &x, const Rational &y);
        friend const Rational operator /(const Rational &x, const Rational &y);
        friend const Rational operator +(const Rational &x, const Rational &y);
        friend const Rational operator -(const Rational &x, const Rational &y);
        friend const Rational operator -(const Rational &x);

        friend bool operator ==(const Rational &x, const Rational &y);
        friend bool operator <(const Rational &x, const Rational &y);
        friend bool operator <=(const Rational &x, const Rational &y);

        bool iszero() const;
        bool smallerthanzero() const;

    private:
        BigInt nume;
        //numerator
        BigInt deno;
        //denominator
    };
}
#endif
