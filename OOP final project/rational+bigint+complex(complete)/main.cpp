#include <iostream>
#include <cstdlib>
#include <string>
#include "Rational.h"
#include "BigInt.h"
#include "Complex.h"
using namespace std;

int main()
{
    using namespace rational;
    using namespace bigint;
    using namespace complex;
    Complex c1,c2;

    cout<<"Input c1 :"<<endl;
    cin>>c1;
    cout<<"Input c2 :"<<endl;
    cin>>c2;
    cout<<endl<<"c1 = "<<c1<<endl;
    cout<<"c2 = "<<c2<<endl;

    cout<<"c1/c2 = "<<c1/c2<<endl;
    cout<<"c1+c2 = "<<c1+c2<<endl;
    cout<<"c1-c2 = "<<c1-c2<<endl;
    cout<<"c1*c2 = "<<c1*c2<<endl;
    return 0;
}
