//  Project - BigInt.h(interface)
//
//  Team No.14(Ä¬¨°³ó¡B±i¨|ºÓ¡B§õ©v¾ì)
//  Name:§õ©v¾ì
//  StudentID:404410082
//  Dept:CSIE
//  Year:2
//

#ifndef BIGINT_H
#define BIGINT_H

#include<iostream>
#include<cstring>
#include<string>
#include<cstdlib>   //malloc reallc abs
#include<algorithm> // reverse max
using namespace std;
typedef int* IntPtr;

namespace bigint
{
    class BigInt
    {
    public:
        BigInt();
        //Initialize, dynamic array size = 10, num = +0, used = 0
        BigInt(long long int input);
        BigInt(string input);
        BigInt(const BigInt& iniObj);
        ~BigInt();

        friend istream& operator >>(istream& instream, BigInt& number);
        friend ostream& operator <<(ostream& outstream, const BigInt& number);
        friend const BigInt operator +(const BigInt& first, const BigInt& second);
        friend const BigInt operator -(const BigInt& first, const BigInt& second);
        friend const BigInt operator -(const BigInt& first);
        friend const BigInt operator *(const BigInt& first, const BigInt& second);
        friend const BigInt operator /(const BigInt& dividend, BigInt& divisor);
        //divisor is not const
        //we need to avoid condition like this divisor = ("000000123")
        //when calculating, we may change divisor.used;
        friend const BigInt operator %(const BigInt& dividend, BigInt& divisor);
        //we call operator /
        bool operator ==(const BigInt& rvalue) const;
        bool operator !=(const BigInt& rvalue) const;
        bool operator >(const BigInt& rvalue) const;
        bool operator <(const BigInt& rvalue) const;
        bool operator <=(const BigInt& rvalue) const;
        BigInt& operator =(const BigInt& rvalue);
        void factorial();
        void absolute();
        //Precondition: argument > 0
        //Postcondition: calling object will save the  factorial answer
    private:
        IntPtr num;
        int size;
        int used;
        int sign;
        // pos = 1, neg = -1;
        void posadjust();
        //Precondition: this->used is known, call when i do '+' or '-'
        //Postcondition: get a accurate postive BigInt
        void negadjust();
        //Precondition: this->used need correct, call when i do '+' or '-'
        //Postcondition: get a accurate negtive BigInt
        void adjust();
        //Precondition: call when i do '*'
        //Postcondition: get a accurate"this->used" and BigInt
        void expand();
        //Precondition: when the bigint used == size -1
        //Postcondition double the size
        string getsection(int index, const int len);
        //Precondition: when divisor->used is known, call when i do '/'
        //Postcondition: get a number to compare with divisor
        void minus(int index, const int b_used ,const BigInt&);
        //Precondition: when do /, index means we calculate which digit, index + b_used is the range we need to minus
        //Postcondition:
        void checkUsed();
        //Precondition: when every digit are correct, that is after posadjust|negadjust
        //Postcondition: get correct used, the condition ("00000123") will not happen
    };
}

#endif
