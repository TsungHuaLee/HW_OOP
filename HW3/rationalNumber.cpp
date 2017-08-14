//李宗樺 404410082 資工二
#include<iostream>
#include<cstdlib>

using namespace std;
class Rational
{
public:
    Rational(int numeratorValue, int denominatorValue);
    //Initialize numerator and denominator
    Rational(int wholeNumber);
    //Initialize numerator as wholeNumber
    Rational();
    //Initialize numerator(1) denominator(0)
    int getNumerator() const {return numerator; }
    //Postcondition: access numerator
    int getDenominator() const {return denominator; }
    //Postcondition: access denominator
    const int gcd(const int& numerator, const int& denominator);
    //Precondition: numerator and denominator are integer
    //Postcondition:  return greatest common divisor
    void normalize();
    //Precondition: numerator != 0 and denominator != 0
    //Postcondition: reduction of a fraction and
    //               pass the negative sign of denominator to numerator if fraction is negative
    friend ostream& operator <<(ostream& outputstream, const Rational& number);

    friend istream& operator >>(istream& inputstream, Rational& number);

    friend Rational operator *(const Rational& front, const Rational& after);
    //Precondition: give two rational object
    //Postcondition: return front * after
    friend Rational operator /(const Rational& front, const Rational& after);
    //Precondition: give two rational object && after != 0
    //Postcondition: return front / after
    friend bool operator ==(const Rational& front, const Rational& after);
    //Precondition: give two rational object
    //Postcondition: compare there are equal or not

    bool operator <(const Rational& after) const;
    //Precondition:
    //Postcondition: if calling object is less than parameter object, then return TRUE
    bool operator <=(const Rational& after) const;
    //Precondition:
    //Postcondition:if calling object is less than or equal to parameter object, then return TRUE
    bool operator >(const Rational& after) const;
    //Precondition:
    //Postcondition: if calling object is bigger than parameter object, then return TRUE
    bool operator >=(const Rational& after) const;
    //Precondition:
    //Postcondition:if calling object is bigger than or equal to parameter object, then return TRUE
    int& operator [](int index);
    //Precondition: index must be 1 or 0
    //Postcondition:  index = 0 return numerator, index = 1 return denominator

private:
    int numerator;
    int denominator;
};

const Rational operator +(const Rational& front, const Rational& after);
//Precondition:
//Postcondition: return front + after
const Rational operator -(const Rational& front, const Rational& after);
//Precondition:
//Postcondition: return front - after
const Rational operator -(const Rational& front);
//Precondition:
//Postcondition: return negation of calling object
//=======================================================================
int main(){
    Rational number1, number2;
    cout<<"Input two  fraction (example : a/b):\n";
    cin>>number1>>number2;
    number1.normalize();
    number2.normalize();

    cout<<"calculation =========================================\n"
        <<number1<<" + "<<number2<<" = "<<number1+number2<<endl
        <<number1<<" - "<<number2<<" = "<<number1-number2<<endl
        <<"negation: "<<-number1<<" "<<-number2<<endl
        <<number1<<" * "<<number2<<" = "<<number1*number2<<endl
        <<number1<<" / "<<number2<<" = "<<number1/number2<<endl;

    cout<<"comparsion =========================================\n";
    if(number1 < number2)
        cout<<number1<<" < "<<number2<<endl;
    if(number1 <= number2)
        cout<<number1<<" <= "<<number2<<endl;
    if(number1 > number2)
        cout<<number1<<" > "<<number2<<endl;
    if(number1 >= number2)
        cout<<number1<<" >= "<<number2<<endl;
    if(number1 == number2)
        cout<<number1<<" == "<<number2<<endl;
    cout<<"member[0] = "<<number1[0]<<", menber[1] = "<<number1[1]<<endl;
    cout<<"member[0] = "<<number2[0]<<", menber[1] = "<<number2[1]<<endl;
}

Rational::Rational(int numeratorValue, int denominatorValue)
                    :numerator(numeratorValue), denominator(denominatorValue)
{}

Rational::Rational(int wholeNumber)
                    :numerator(wholeNumber), denominator(1)
{}

Rational::Rational()
                    :numerator(0), denominator(1)
{}


//friend===========================================================
ostream& operator <<(ostream& outputstream, const Rational& number)
{
    outputstream<<number.numerator<<"/"<<number.denominator;
    return outputstream;
}

istream& operator >>(istream& inputstream, Rational& number)
{
    char slash;
    inputstream>>number.numerator>>slash>>number.denominator;
    return inputstream;
}

Rational operator *(const Rational& front, const Rational& after)
{
    int newNumerator = front.numerator * after.numerator;
    int newDenominator = front.denominator * after.denominator;
    Rational temp(newNumerator, newDenominator);
    temp.normalize();
    return temp;
}

Rational operator /(const Rational& front, const Rational& after)
{
    int newNumerator = front.numerator * after.denominator;
    int newDenominator = front.denominator * after.numerator;
    Rational temp(newNumerator, newDenominator);
    temp.normalize();
    return temp;
}

bool operator ==(const Rational& front, const Rational& after)
{
    if((front.numerator * after.denominator) == (front.denominator * after.numerator))
        return true;
    else
        return false;
}

//member=================================================================
const int Rational::gcd(const int& a, const int& b){
    if(b == 0)
        return a;
    else
        return gcd(b, a % b);
}

void Rational::normalize(){
    if(denominator < 0)     //pass the negative sign of denominator to numerator if fraction is negative
    {
        denominator = abs(denominator);
        numerator = -numerator;
    }
    int divide = abs(gcd(numerator, denominator));
    numerator /= divide;
    denominator /= divide;

    return ;
}

bool Rational::operator <(const Rational& after) const
{
    if((numerator * after.denominator) < (denominator * after.numerator))
        return true;
    else
        return false;
}

bool Rational::operator <=(const Rational& after) const
{
    if((numerator * after.denominator) <= (denominator * after.numerator))
        return true;
    else
        return false;
}

bool Rational::operator >(const Rational& after) const
{
    if((numerator * after.denominator) > (denominator * after.numerator))
        return true;
    else
        return false;
}

bool Rational::operator >=(const Rational& after) const
{
    if((numerator * after.denominator) >= (denominator * after.numerator))
        return true;
    else
        return false;
}

int& Rational::operator [](int index)
{
    if(index == 0)
        return numerator;
    else if(index == 1)
        return denominator;
    else{
        cout<<index<< " is Illegal index \n";
        exit(1);
    }
}
//nonmember=================================================================
const Rational operator +(const Rational& before, const Rational& after)
{
    int newNumerator = (before.getNumerator() * after.getDenominator()) + (before.getDenominator() * after.getNumerator());
    int newDenominator = before.getDenominator() * after.getDenominator();
    Rational temp(newNumerator, newDenominator);
    temp.normalize();
    return temp;
}

const Rational operator -(const Rational& before, const Rational& after)
{
    int newNumerator = (before.getNumerator() * after.getDenominator()) - (before.getDenominator() * after.getNumerator());
    int newDenominator = before.getDenominator() * after.getDenominator();
    Rational temp(newNumerator, newDenominator);
    temp.normalize();
    return temp;
}

const Rational operator -(const Rational& number)
{
    return Rational(-number.getNumerator(), number.getDenominator());
}
