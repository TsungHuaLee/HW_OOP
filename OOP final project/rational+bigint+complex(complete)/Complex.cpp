#include <iostream>
#include <cstdlib>
#include <string>

#include "Complex.h"
#include "Rational.h"
#include "BigInt.h"
using namespace bigint;
using namespace rational;

namespace complex
{
    Complex::Complex()
    {   }
    Complex::Complex(Rational a, Rational b)
                :real(a),imaginary(b)
    {   }
    Complex::Complex(Rational only_a)
                :real(only_a)
    {   }

    ostream& operator << (ostream& output, const Complex &out)
    {
        output<<out.real;
        if(out.imaginary.iszero())
            return output;
        if(out.imaginary.smallerthanzero())
        {
            output<<" - ("<<-out.imaginary<<") i ."<<endl;
        }
        else
        {
            output<<" + ("<<out.imaginary<<") i ."<<endl;
        }
        return output;
    }

    istream& operator >> (istream& input, Complex &in)
    {
        cout<< "input real number : (a/b)";
        input>>in.real;
        cout<< "input imaginary number : (a/b)";
        input>>in.imaginary;
        return input;
    }
    const Complex& Complex::operator = (const Complex& right)
    {
        if(this==&right)
            return *this;
        else
        {
            this->real=right.real;
            this->imaginary=right.imaginary;
            return *this;
        }
    }
    const Complex operator +(const Complex &a , const Complex &b)
    {
        Complex temp;
        temp.real = a.real+b.real;
        temp.imaginary = a.imaginary + b.imaginary;
        return temp;
    }
    const Complex operator -(const Complex &a , const Complex &b)
    {
        Complex temp;
        temp.real = a.real-b.real;
        temp.imaginary = a.imaginary - b.imaginary;
        return temp;
    }
    const Complex operator *(const Complex &a , const Complex &b)
    {
        Complex temp;
        temp.real = a.real*b.real - a.imaginary*b.imaginary;
        temp.imaginary = a.imaginary*b.real + a.real*b.imaginary;
        return temp;

    }
    const Complex operator /(const Complex &a , const Complex &b)
    {

        Complex temp;
        Rational AC_BD,CC_DD,BC_AD;
        using namespace rational;
        {
            AC_BD = a.real*b.real + a.imaginary*b.imaginary;
            BC_AD = a.imaginary*b.real + a.real*b.imaginary;
            CC_DD = b.real*b.real + b.imaginary*b.imaginary;
            temp.real = AC_BD / CC_DD;
            temp.imaginary = BC_AD / CC_DD;
        }

        return temp;
    }
}

