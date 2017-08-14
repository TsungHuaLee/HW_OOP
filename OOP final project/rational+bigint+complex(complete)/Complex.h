#ifndef COMPLEX_H
#define COMPLEX_H

#include<iostream>
#include<string>
#include "BigInt.h"
#include "Rational.h"

using namespace bigint;
using namespace rational;

namespace complex
{
    class Complex
    {
        public:
            Complex();
            Complex(Rational a,Rational b);
            Complex(Rational only_a);
            const Complex& operator = (const Complex& right);
            friend ostream& operator <<(ostream& output, const Complex &out);
            friend istream& operator >>(istream& input , Complex &in);
            friend const Complex operator + (const Complex &a , const Complex &b);
            friend const Complex operator - (const Complex &a , const Complex &b);
            friend const Complex operator * (const Complex &a , const Complex &b);
            friend const Complex operator / (const Complex &a , const Complex &b);

        private:
            Rational real;
            Rational imaginary;
    };
}
#endif // COMPLEX_H

