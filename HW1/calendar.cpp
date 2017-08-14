// 李宗樺 404410082 CSIE sophomore
#include<iostream>
#include<iomanip>
using namespace std;

bool inputYrMn(int& year,int& month);
//Precondition: year and month are the calendar you want to know.
//Postcondition: input data,return the year and the month is valid or not.
int isLeap(int year);
//Precondition: year must be valid.
//Postcondition: return this year is leap or not.
void get1stDayOfMonth(int year, int month, int& firstWeekday, int& numOfDay);
//Precondition: year and month are valid.
//Postcondition: return the first day and the number of day of the month.
void showCalendar(int year, int month, int firstWeekday, int numOfDay);
//Precondition: use funtion get1stDayOfMonth to get firstWeekday and numOfDay.
//Postcondition: print the month following format.

int main() {
    while(1){
        int year(0),month(0),firstWeekday(0),numOfDay(0);
        cout<<"Input year(1901~2099) and month"<<endl;
        while(!inputYrMn(year, month));  //input data
        get1stDayOfMonth(year, month, firstWeekday, numOfDay);
        showCalendar(year, month, firstWeekday, numOfDay);
        cout<<"Press y/Y to continue:";
        char flag;
        cin>>flag;
        if(flag != 'y' && flag != 'Y')
            break;
  }
    return 0;
}

bool inputYrMn(int& year, int& month){
    cout<<"Year Month:";
    cin>>year>>month;
    if(year >= 1901 && year <= 2099){ //judge this year and month is valid
        if(month >=1 && month<=12)
            return true;
        else{
            cout<<"Invalid month"<<endl;
            return false;
        }
    }
    else{
      cout<<"Invalid year"<<endl;
      return false;
    }
}
int isLeap(int year){
    return  (year%400==0) || ((year%4==0)&&(year%100!=0));
}
void get1stDayOfMonth(int year, int month, int& firstWeekday, int& numOfDay){
    int days[]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    days[2] += isLeap(year);
    numOfDay = days[month];
    //use Zeller formula: weekday =( year + year/4 + century/4 - 2*century + (26*(month+1)/10) + day -1 ) %7
    //January & February 要算是上一年的 13 & 14 月
    int century = year/100;
    switch (month) {
      case 1:
      month = 13;
      year--;
      break;
      case 2:
      month = 14;
      year--;
      break;
    }
    firstWeekday =(year%100) + (year%100)/4 + century/4 - 2*century + (26*(month+1)/10) + 1 - 1;
    //prevent firstWeekday being negative;
    firstWeekday =(firstWeekday % 7 + 7) % 7;
    return ;
}
void showCalendar(int year, int month,int firstWeekday, int numOfDay)
{
    string monthInEnglish[13]={"0","January","February","March","April","May","June","July","August","September","October","November","December"};
    cout<<"-----------------------------"<<endl
        <<"          "<<year<<" "<<monthInEnglish[month]<<"               "<<endl
        <<"-----------------------------"<<endl
        <<" SUN MON TUE WED THU FRI SAT "<<endl;
    //print space before the firstWeekday.
    for(int i=0; i<firstWeekday; i++)
        cout<<"    ";
    for(int i=0, count=firstWeekday+1 ; i<numOfDay; i++, count++)
    {
        cout<<setw(4)<<i+1;
        if(count % 7 == 0 && i != numOfDay-1 )  // &&(~) 保護格式
            cout<<endl;
    }
    cout<<endl<<"-----------------------------"<<endl;
    return ;
}
