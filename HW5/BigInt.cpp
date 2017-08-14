#include "BigInt.h"
#include<cstdlib>
namespace bigint
{
BigInt::BigInt()
{
    //check sign
    this->sign = 1;
    //initialize size
    this->num = new int[10];
    this->size = 10;
    //used initial num = 0
    memset(this->num, 0, sizeof(int)*10);
    //check used
    this->used = 0;
}

BigInt::BigInt(long long int input)
{
    //check sign
    if(input < 0)
    {
        input = abs(input);
        this->sign = -1;
    }
    else
        this->sign = 1;
    //initialize size
    this->num = new int[10];
    this->size = 10;
    //used initial  num =0
    memset(this->num, 0, sizeof(int)*10);

    //input == 0 + check used
    if(input == 0)
    {
        this->used = 1;
        this->num[0] = input;
    }//input != 0 + check used
    else
    {
        for(this->used = 0; input != 0; input/=10, this->used++)
        {
            if(this->used == this->size - 1)
                this->expand();
            this->num[this->used] = (input % 10);
        }
    }

}

BigInt::BigInt(string input)
{
    //check sign
    if(input[0] == '-')
        {
            this->sign = -1;
            input.erase(input.begin());
        }
    else
        this->sign = 1;
    //initialize size
    this->size = 2*input.length();
    this->num = new int;
    this->num = (int*)malloc(sizeof(int)*this->size);
    //unused initialize num 0
    memset(this->num, 0, sizeof(int)*this->size);
    //input = 0 or input != 0 doesn't matter +  check used
    reverse(input.begin(), input.end());
    for(this->used = 0; this->used < input.length(); this->used++)
    {
        this->num[this->used] = input[this->used]-'0';
    }
}

BigInt::BigInt(const BigInt& iniObj)
{
    //check sign
    this->sign = iniObj.sign;
    //initialize size
    this->num = new int[iniObj.size];
    //unused initialize  num 0
    memset(this->num, 0, sizeof(int)*iniObj.size);
    //num + check used
    for(this->size = iniObj.size, this->sign = iniObj.sign, this->used = 0; this->used < iniObj.used; this->used++)
        this->num[this->used] = iniObj.num[this->used];
}

BigInt::~BigInt()
{
    delete [] this->num;
    this->num = NULL;
}
//=============================================================================
void BigInt::expand()
{
    //double size
    this->size *= 2;
    this->num = (int*)realloc(this->num, sizeof(int)*this->size);
    // unused array initialize 0
    for(int i = this->used; i < this->size; i++)
        this->num[i] = 0;
    return;
}

void BigInt::factorial()
{
    BigInt temp = *this;
    *this = 1;
    while(temp != 0)
    {
        *this = *this * temp;
        temp = temp - 1;
    }

    return;
}

void BigInt::absolute()
{
    this->sign = 1;
    return;
}
void BigInt::posadjust()
{

    //correct number
    for(int i = 0; i < this->used; i++)
    {
        //borrow
        if(this->num[i] < 0)
        {
            this->num[i] += 10; //neg -> pos
            this->num[i + 1] --;//borrow from bigger digit
        }
        //carry
        this->num[i+1] += this->num[i]/10;
        this->num[i] = this->num[i]%10;
    }

    //check used, possible decrease many digit
    this->checkUsed();
    return;
}

void BigInt::negadjust()
{
    //correct number
    for(int i = 0; i < this->used; i++)
    {
        //borrow
        if(this->num[i] > 0)
        {
            this->num[i] -= 10; //pos ->neg
            this->num[i + 1]++; // borrow from bigger digit
        }
        //carry
        this->num[i+1] += this->num[i]/10;
        this->num[i] = this->num[i]%10;
    }
    // have sign bit, so let every digit be pos
    for(int i = 0; i < this->used; i++)
        this->num[i] = abs(this->num[i]);
    //check used, possible decrease many digit
        this->checkUsed();
    return;
}

void BigInt::adjust()
{
    for(int i = 0; i < this->size; i++)
    {
        this->num[i + 1] +=this->num[i] / 10;
        this->num[i] = this->num[i] % 10;
        //when num != 0 check it is biggist digit and change used
        if(this->num[i])
        {
            this->used = max(this->used, i);
        }
    }
    //convinent to code and read
    this->used += 1;
    return;
}

string BigInt::getsection(int index, const int len)
{
    string str;
    for(int k =(index + len - 1); k >= index; k--)
        {
            str+=this->num[k]+'0';
        }
    return str;
}

void BigInt::minus(int index, const int tominusUsed, const BigInt& tominus)
{
    for(int k =(index + tominusUsed - 1), j = tominusUsed - 1; k >= index; k--, j--)
        {
            this->num[k] -= tominus.num[j];
        }
    this->posadjust();
    return;
}

void BigInt::checkUsed()
{
    for(int i = this->size - 1; i >= 0; i--)
    {
        if(this->num[i] != 0)
        {   // convinent to code
            this->used = i + 1;
            break;
        }
        //number = 0, used = 1
        if(i == 0)
            this->used = 1;
    }
    return;
}

istream& operator >>(istream& instream, BigInt& number)
{
    string input;
    instream>>input;
    BigInt temp(input);
    number = temp;
    return instream;
}
ostream& operator <<(ostream& outstream, const BigInt& number)
{
    if(number.sign==-1)
        outstream<<"-";
    for(int i = number.used - 1; i >= 0 ;i-- )
        outstream<<number.num[i];
    return outstream;
}
//at first, every digit compute independent, then adjust
const BigInt operator +(const BigInt& first, const BigInt& second)
{
    int longer = max(first.used, second.used);
    BigInt front(first), after(second);
    //to avoid calculate out of range
    while(longer > front.size)
        front.expand();
    while(longer > after.size)
        after.expand();

    BigInt temp;
    //calculate
    for(int i = 0; i < longer; i++)
    {
        if(i == temp.size - 1)
            temp.expand();

        temp.num[i] = (front.sign*front.num[i] + after.sign*after.num[i]);
        temp.used++; //when i do expand , i need this used;
    }

    //check how many used
    temp.checkUsed();
    //check sign, adjust number
    //after adjust the value of used may change
    if(temp.num[temp.used - 1] > 0) //posadjust
    {
        temp.sign = 1;
        temp.posadjust();
    }
    else if(temp.num[temp.used - 1]  < 0) //negadjust
    {
        temp.sign = -1;
        temp.negadjust();
    }
    // 0 sign = 1
    else
        temp.sign = 1;
    return temp;
}
//at first, every digit compute independent, then adjust
const BigInt operator -(const BigInt& first, const BigInt& second)
{
    int longer = max(first.used, second.used);
    BigInt front(first), after(second);
    //to avoid calculate out of range
    while(longer > front.size)
        front.expand();
    while(longer > after.size)
        after.expand();

    BigInt temp;
    for(int  i = 0; i < longer; i++)
    {
        //can borrow
        if( i == temp.size -1)
            temp.expand();
        temp.num[i] = (front.sign*front.num[i] - after.sign*after.num[i]);
        temp.used++;
    }

    //check how many used
    temp.checkUsed();

    //check sign, adjust number
    //after adjust the value of used may change
    if(temp.num[temp.used - 1] > 0) //posadjust
        {
            temp.sign = 1;
            temp.posadjust();
        }
    else if(temp.num[temp.used - 1]  < 0) //negadjust
    {
        temp.sign = -1;
            temp.negadjust();
    }
    // 0 sign = 1
    else
        temp.sign = 1;

    return temp;
}

const BigInt operator -(const BigInt& first)
{
    BigInt temp(first);
    temp.sign *= -1;
    return temp;
}

//at first, every digit compute independent, then adjust
const BigInt operator*(const BigInt& first, const BigInt& second)
{
    BigInt temp;
    //check sign;
    (first.sign == second.sign)?temp.sign = 1 : temp.sign = -1;
    //check size;
    while(temp.size < (first.used + 1) + (second.used + 1))
        temp.expand();
    //calculate
    for(int i = 0; i < first.used; i++)
        for(int j = 0; j < second.used; j++)
        {
            temp.num[i + j] += first.num[i] * second.num[j];
        }
    temp.adjust();

    return temp;
}

const BigInt operator /(const BigInt& dividend, BigInt& divisor)
{
    //because constructor (string) allow condition like this ("000001")
    //to avoid calculation error, divisor should remove this unused 0
    //check divisor used again
    divisor.checkUsed();

    if(divisor == 0)
    {
        cout<<"Invalid divisor";
        exit(0);
    }
    //number divisor > dividend
    if(divisor.used> dividend.used)
        return 0;

    BigInt remainder(dividend);
    BigInt quotient;
    for(int i = (dividend.used - divisor.used), k = 0; i >= 0; i--, k++)
    {
        string section = remainder.getsection(i, divisor.used + 1);
        BigInt tocompare(section);

        for(int j = 9; j >= 0; j--)
        {
            BigInt temp;

            temp = divisor * j;
            temp.absolute();
            //By long division, find the fist divisor*j < tocompare
            //the j will be the part of quotient
            if(temp <= tocompare)
            {
                quotient = quotient*10 + j ;
                remainder.minus(i, temp.used, temp);
                break;
            }
        }
    }
    quotient.sign = dividend.sign*divisor.sign;
    return quotient;
}

const BigInt operator %(const BigInt& dividend, BigInt& divisor)
{
    BigInt quotient = dividend / divisor;
    BigInt remainder = dividend - (divisor*quotient);

    return remainder;
}

bool BigInt::operator ==(const BigInt& rvalue)const
{
    if((this->sign != rvalue.sign))
        return false;
    for(int i = this->used - 1; i >= 0; i--)
        if(this->num[i] != rvalue.num[i])
            return false;

    return true;
}

bool BigInt::operator !=(const BigInt& rvalue)const
{
    if((this->sign != rvalue.sign))
        return true;
    for(int i = this->used - 1; i >= 0; i--)
        if(this->num[i] != rvalue.num[i])
            return true;

    return false;
}

bool BigInt::operator >(const BigInt& rvalue)const
{
    if(*this == rvalue)
        return false;
    // + > -
    if(this->sign > rvalue.sign){
        return true;
    }

    int longer;
    longer = (this->used>rvalue.used)?this->used : rvalue.used;
    //when same sign, compare
    if(this->sign == 1)
    {
        for(int i = longer -1; i >= 0; i--)
        {
            if(this->num[i] > rvalue.num[i])
                return true;
            else if(this->num[i] == rvalue.num[i])
                continue;
            else
                return false;
        }
    }
    if(this->sign == -1)
    {
        for(int i = longer -1; i >= 0; i--)
        {
            if(this->num[i] > rvalue.num[i])
                return false;
            else if(this->num[i] == rvalue.num[i])
                continue;
            else
                return true;
        }
    }
}

bool BigInt::operator <(const BigInt& rvalue)const
{
    if(*this == rvalue)
        return false;
    // - < +
    if(this->sign < rvalue.sign){
        return true;
    }

    int longer;
    longer = (this->used>rvalue.used)?this->used : rvalue.used;

    //when same sign, compare
    if(this->sign == 1)
    {
        for(int i = longer -1; i >= 0; i--)
        {
            if(this->num[i] < rvalue.num[i])
                return true;
            else if(this->num[i] == rvalue.num[i])
                continue;
            else
                return false;
        }
    }
    if(this->sign == -1)
    {
        for(int i = longer -1; i >= 0; i--)
        {
            if(this->num[i] > rvalue.num[i])
                return true;
            else if(this->num[i] == rvalue.num[i])
                continue;
            else
                return false;
        }
    }
}

bool BigInt::operator <=(const BigInt& rvalue)const
{
    if(*this == rvalue)
        return true;
    // - < +
    if(this->sign < rvalue.sign)
        return true;

    int longer;
    longer = (this->used>rvalue.used)?this->used : rvalue.used;
    //when same sign, compare
    if(this->sign == 1)
    {
        for(int i = longer -1; i >= 0; i--)
        {
            if(this->num[i] < rvalue.num[i])
                return true;
            else if(this->num[i] == rvalue.num[i])
                continue;
            else
                return false;
        }
    }
    if(this->sign == -1)
    {
        for(int i = longer -1; i >= 0; i--)
        {
            if(this->num[i] > rvalue.num[i])
                return true;
            else if(this->num[i] == rvalue.num[i])
                continue;
            else
                return false;
        }
    }
}

BigInt& BigInt::operator =(const BigInt& rvalue)
{
    if(this == &rvalue)
        return *this;
    this->num = (int*)realloc(this->num, sizeof(int)* rvalue.size);
    for(int i = 0; i < rvalue.size; i++)
        this->num[i] = rvalue.num[i];
    this->size = rvalue.size;
    this->used = rvalue.used;
    this->sign = rvalue.sign;
    return *this;
}

}
