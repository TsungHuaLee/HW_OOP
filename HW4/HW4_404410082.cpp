//李宗樺 404410082 資工二
#include<iostream>
#include<cstring>
#include<string>
#include<cstdlib>   //malloc reallc abs
#include<algorithm> // reverse max
using namespace std;
typedef int* IntPtr;
class BigInt
{
public:
    BigInt();
    BigInt(long long int input);
    BigInt(string input);
    BigInt(const BigInt& iniObj);
    ~BigInt();

    friend ostream& operator <<(ostream& outstream, const BigInt& number);
    friend const BigInt operator +(const BigInt& first, const BigInt& second);
    friend const BigInt operator -(const BigInt& first, const BigInt &second);
    BigInt& operator =(const BigInt& rvalue);
    void expand();
    //Precondition: when the bigint used == size -1
    //Postcondition double the size
private:
    IntPtr num;
    int size;
    int used;
    int sign;
};

int main()
{

    BigInt a("31415926535897"),c(a);
    BigInt *b = new BigInt(1618033988);
    c = a + *b;
    cout<< a << " + "<<*b<<" = "<<c<<endl;
    c = a - *b;

    cout<<a <<" - "<< *b<<" = "<< c;
}

BigInt::BigInt()
{
    this->num = new int[10];
    this->size = 10;
    this->used = 0;
    this->sign = 1;
    //used initial 0
    memset(this->num, 0, sizeof(int)*10);
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
    //initialize
    this->num = new int[10];
    this->size = 10;
    //copy
    for(this->used = 0; input != 0; input/=10, this->used++)
    {
        if(this->used == this->size - 1)
            this->expand();
        this->num[this->used] = (input % 10);
    }
}

BigInt::BigInt(string input)
{
    //check sign
    if(input[0] == '-')
        {
            sign = -1;
            input.erase(input.begin());
        }
    else
        sign = 1;
    //initialize
    this->size = 2*input.length();
    this->num = new int;
    this->num = (int*)malloc(sizeof(int)*this->size);
    //unused initialize 0
    memset(this->num, 0, sizeof(int)*this->size);
    //copy
    reverse(input.begin(), input.end());
    for(this->used = 0; this->used < input.length(); this->used++)
    {
        this->num[this->used] = input[this->used]-'0';
    }
}

BigInt::BigInt(const BigInt& iniObj)
{
    this->num = new int[iniObj.size];
    //unused initialize 0
    memset(this->num, 0, sizeof(int)*iniObj.size);
    //copy
    for(this->size = iniObj.size, this->sign = iniObj.sign, this->used = 0; this->used < iniObj.used; this->used++)
        this->num[this->used] = iniObj.num[this->used];
}

BigInt::~BigInt()
{
    delete [] this->num;
    this->num = NULL;
}

void BigInt::expand()
{
    //double size
    this->size *= 2;
    this->num = (int*)realloc(this->num, sizeof(int)*this->size);
    // unused initialize 0
    for(int i = this->used; i < this->size; i++)
        this->num[i] = 0;

    return;
}


ostream& operator <<(ostream& outstream, const BigInt& number)
{
//    outstream<<"\nsize  used  number\n";
//    outstream<<number.size<<" "<<number.used<<" ";
    if(!number.sign)
        outstream<<"-";
    for(int i = number.used - 1; i >= 0 ;i-- )
        outstream<<number.num[i];
    return outstream;
}

const BigInt operator +(const BigInt& first, const BigInt& second)
{
    int longer = max(first.used, second.used);
    BigInt temp;
    //compute
    for(int i = 0; i < longer; i++)
    {
        if(i == temp.size - 1)
            temp.expand();
        temp.num[i] = (first.num[i] + second.num[i])%10;
        if(i != 0)
            temp.num[i] +=(first.num[i-1] + second.num[i-1])/10;
        temp.used++;
        cout<<i<<" "<<temp.num[i]<<endl;
    }

    //set how many used
    for(int i = temp.size - 1; i >= 0; i--)
    {
        if(temp.num[i] != 0)
        {
            temp.used = i + 1;
            break;
        }
        //number = 0, used = 1
        if(i == 0)
            temp.used = 1;
    }

    return temp;
}

const BigInt operator -(const BigInt& first, const BigInt& second)
{
    int longer = max(first.used, second.used);
    BigInt temp(first);
    for(int  i = 0; i < longer; i++)
    {
        //can borrow
        if( i == temp.size -1)
            temp.expand();
        if((i < first.used - 1) && (first.num[i] < second.num[i]))
            {
                temp.num[i]  = temp.num[i] + 10 - second.num[i];
                temp.num[i+1] --;
            }
        else
            temp.num[i] = temp.num[i] - second.num[i];

    }
    return temp;
}

BigInt& BigInt::operator =(const BigInt& rvalue)
{
    this->num = (int*)realloc(this->num, sizeof(int)* rvalue.size);
    for(int i = 0; i < rvalue.size; i++)
        this->num[i] = rvalue.num[i];
    this->size = rvalue.size;
    this->used = rvalue.used;
    this->sign = rvalue.sign;
    return *this;
}
