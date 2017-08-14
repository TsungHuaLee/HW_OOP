//  Project - Rational.cpp(implementation)
//
//  Team No.14(蘇辰堯、張育碩、李宗樺)
//  Name:張育碩
//  StudentID:404410047
//  Dept:CSIE
//  Year:2
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <ctime>
#include <windows.h>
#include "Rational.h"
#include "BigInt.h"
using std::istream;
using std::ostream;
using std::cin;
using std::cout;
using bigint::BigInt;

namespace
{
    BigInt gcd(BigInt m, BigInt n)
    {
        m.absolute();
        n.absolute();
        while(n != 0)
        {
            BigInt r = m % n;
            m = n;
            n = r;
        }
        return m;
    }

    void normalize(BigInt &m, BigInt &n)
    {
        BigInt d = gcd(m,n);
        m = m / d;
        n = n / d;
    }
}

namespace rational
{
    Rational::Rational()
                :nume(0), deno(1)
    {

    }

    Rational::Rational(BigInt n, BigInt d)
                :nume(n), deno(d)
    {

    }

    Rational::Rational(BigInt wholeNumber)
                :nume(wholeNumber), deno(1)
    {

    }

    Rational::Rational(const Rational &iniObj)
    {
        nume = iniObj.nume;
        deno = iniObj.deno;
    }

    Rational& Rational::operator =(const Rational &rside)
    {
        if(this == &rside)
            return *this;
        else
        {
            nume = rside.nume;
            deno = rside.deno;
            return *this;
        }
    }

    bool Rational::iszero() const
    {
        if(nume == 0)
            return 1;
        else
            return 0;
    }

    bool Rational::smallerthanzero() const
    {
        if((nume * deno) < 0)
            return 1;
        else
            return 0;
    }

    const Rational operator +(const Rational &x, const Rational &y)
    {
        BigInt numx = x.nume;
        BigInt denox = x.deno;
        BigInt numy = y.nume;
        BigInt denoy = y.deno;
        BigInt deno = denox * denoy;
        numx = numx * denoy;
        numy = numy * denox;
        numx = numx + numy;
        normalize(numx,deno);
        return Rational(numx,deno);
    }

    const Rational operator -(const Rational &x, const Rational &y)
    {
        BigInt numx = x.nume;
        BigInt denox = x.deno;
        BigInt numy = y.nume;
        BigInt denoy = y.deno;
        BigInt deno = denox * denoy;
        numx = numx * denoy;
        numy = numy * denox;
        numx = numx - numy;
        normalize(numx,deno);
        return Rational(numx,deno);
    }

    const Rational operator -(const Rational &x)
    {
        BigInt num = x.nume;
        BigInt deno = x.deno;
        num = -num;
        return Rational(num,deno);
    }

    ostream& operator <<(ostream& output, const Rational &n)
    {
        BigInt num, deno;
        num = n.nume;
        deno = n.deno;
        if((num < 0 && deno < 0) || (deno < 0))
        {
            num = -num;
            deno = -deno;
        }
        normalize(num,deno);
        output << num;
        output << '/';
        output << deno;
        return output;
    }

    istream& operator >>(istream& input, Rational &n)
    {
        string insertion;
        input >> insertion;
        int flag = 0;
        stringstream ss(insertion);
        string token;
        while(getline(ss, token, '/'))
        {
            if(flag == 0)
            {
                if(token[token.length() - 1] == '!')
                {
                    token.erase(token.length() - 1);
                    BigInt num(token);
                    num.factorial();
                    n.nume = num;
                }
                else
                {
                    BigInt num(token);
                    n.nume = num;
                }
                flag++;
            }
            else
            {
                if(token[token.length() - 1] == '!')
                {
                    token.erase(token.length() - 1);
                    BigInt deno(token);
                    deno.factorial();
                    n.deno = deno;
                }
                else
                {
                    BigInt deno(token);
                    n.deno = deno;
                }
            }
        }
        return input;
    }

    const Rational operator *(const Rational &x, const Rational &y)
    {
        BigInt multinum = x.nume * y.nume;
        BigInt multideno = x.deno * y.deno;
        normalize(multinum,multideno);
        return Rational(multinum,multideno);
    }

    const Rational operator /(const Rational &x, const Rational &y)
    {
        BigInt multinum = x.nume * y.deno;
        BigInt multideno = x.deno * y.nume;
        normalize(multinum,multideno);
        return Rational(multinum,multideno);
    }

    bool operator ==(const Rational &x, const Rational &y)
    {
        return ((x.nume * y.deno) == (x.deno * y.nume));
    }

    bool operator<(const Rational &x, const Rational &y)
    {
        return ((x.nume * y.deno) < (x.deno * y.nume));
    }

    bool operator<=(const Rational &x, const Rational &y)
    {
        return ((x.nume * y.deno) <= (x.deno * y.nume));
    }

}


