// 李宗樺 404410082 CSIE sophomore
#include<iostream>
#include<cstdlib>
#include<windows.h>
using namespace std;
class GameOfLife
{
public:
    GameOfLife(int widthValue, int heightValue);
    //Initialize the width and height to arguments
    GameOfLife();
    //Initialize the width(80) and height(23)
    void initialize(int pattern);
    //Precondition: 1 <= pattern <=100
    //Postcondition: Initialize the map with the pattern.
    void proceed(int timeValue);
    //Precondition: function will execute timeValue generation.
    //Postcondition: determine every cell with live or dead.
    void display();
    //Postcondition: print currently cell.
private:
    int width;
    int height;
    int cell[260][260];  // max with and height is 256
    int temp[260][260];
    void glider();
    //Postcondition:Set the map with the glider pattern.
    void spaceship();
    //Postcondition:Set the map with the spaceship pattern.
    void pulsar();
    //Postcondition:Set the map with the pulsar pattern.
    void random(int pattern);
    //Precontidion: 4 <= pattern <= 100
    //Postcondition:Input pattern number is the percentage of live cells.
};

int main()
{
    char flag;
    do{
        int pattern;
        char changeBuffer;
        cout<<"Input pattern between 1 and 100(1:glider, 2:spaceship, 3:pulsar, 4:random): ";
        cin>>pattern;
        cout<<"\nDo you wnat to change width, height, times (default: 80,23,100) ?\n (y/n) ";
        cin>>changeBuffer;
        if(changeBuffer == 'y' || changeBuffer == 'Y')
        {
            int widthValue,heightValue,timeValue;
            cout<<"\nwidth  height times \n";
            cin>>widthValue>>heightValue>>timeValue;
            GameOfLife settlement(widthValue,heightValue);
            settlement.initialize(pattern);
            settlement.proceed(timeValue);
            settlement.display();
        }
        else
        {
            GameOfLife settlement;
            settlement.initialize(pattern);
            settlement.proceed(100);
            settlement.display();
        }
        cout<<"\n Press y/Y to continue :";
        cin>>flag;
    }while(flag == 'y' || flag == 'Y');
}

GameOfLife::GameOfLife(int widthValue, int heightValue)
                    : width(widthValue), height(heightValue)
{
}

GameOfLife::GameOfLife():width(80),height(23)
{   }

void GameOfLife::initialize(int pattern)
{
    memset(cell, 0, sizeof(int)*260*260);
    memset(temp, 0, sizeof(int)*260*260);
    if(pattern == 1)
        glider();
    else if(pattern == 2)
        spaceship();
    else if(pattern == 3)
        pulsar();
    else
        random(pattern);
    return;
}

void GameOfLife::glider()
{
    const int startY = (height-3)/2, startX = (width-3)/2;
    cell[startY][startX] = 1;
    cell[startY][startX + 1] = 1;
    cell[startY][startX + 2] = 1;
    cell[startY + 1][startX] = 1;
    cell[startY + 2][startX + 1] = 1;
    return;
}
void GameOfLife::spaceship()
{
    const int startY = (height-4)/2, startX = (width-5)/2;
    cell[startY][startX + 1] = 1;
    cell[startY][startX + 4] = 1;
    cell[startY + 1][startX] = 1;
    cell[startY + 2][startX] = 1;
    cell[startY + 2][startX + 4] = 1;
    for(int i=startX; i<startX + 4; i++)
        cell[startY + 3][i] = 1;
    return;
}
void GameOfLife::pulsar()
{
    const int startY = (height-13)/2, startX = (width-13)/2;
    cell[startY][startX + 2] = 1;
    cell[startY][startX + 3] = 1;
    cell[startY][startX + 9] = 1;
    cell[startY][startX + 10] = 1;
    cell[startY + 1][startX + 3] = 1;
    cell[startY + 1][startX + 4] = 1;
    cell[startY + 1][startX + 8] = 1;
    cell[startY + 1][startX + 9] = 1;
    cell[startY + 2][startX] =1;
    cell[startY + 2][startX + 3] =1;
    cell[startY + 2][startX + 5] =1;
    cell[startY + 2][startX + 7] =1;
    cell[startY + 2][startX + 9] =1;
    cell[startY + 2][startX + 12] =1;
    for(int i = startX; i < startX + 13; i++)
        if((i != startX + 3) && (i != startX + 6) && (i != startX + 9))
            cell[startY + 3][i] = 1;
    for(int i = startX; i < startX + 13; i++)
        if( ((i - startX) % 2) == 1)
            cell[startY + 4][i] = 1;
    for(int i = startX + 2 ; i < startX + 11; i++){
        cell[startY + 5][i] = 1;
        if(i ==startX + 4)
            i += 3;
    }

    cell[startY + 12][startX + 2] = 1;
    cell[startY + 12][startX + 3] = 1;
    cell[startY + 12][startX + 9] = 1;
    cell[startY + 12][startX + 10] = 1;
    cell[startY + 11][startX + 3] = 1;
    cell[startY + 11][startX + 4] = 1;
    cell[startY + 11][startX + 8] = 1;
    cell[startY + 11][startX + 9] = 1;
    cell[startY + 10][startX] =1;
    cell[startY + 10][startX + 3] =1;
    cell[startY + 10][startX + 5] =1;
    cell[startY + 10][startX + 7] =1;
    cell[startY + 10][startX + 9] =1;
    cell[startY + 10][startX + 12] =1;
    for(int i = startX; i < startX + 13; i++)
        if((i != startX + 3) && (i != startX + 6) && (i != startX + 9))
            cell[startY + 9][i] = 1;
    for(int i = startX; i < startX + 13; i++)
        if( ((i - startX) % 2) == 1)
            cell[startY + 8][i] = 1;
    for(int i = startX + 2 ; i < startX + 11; i++){
        cell[startY + 7][i] = 1;
        if(i ==startX + 4)
            i += 3;
    }
}

void GameOfLife::random(int pattern)
{
    for(int i=0; i<width; i++)
        for(int j=0; j<height; j++)
            {
                int temp = (rand() % 100) + 1;
                if(temp < pattern)
                    cell[i][j] = 1;
            }
    return;
}

void GameOfLife::proceed(int timeValue)
{
    while(timeValue--)
    {
        display();
        for(int row = 0; row < height; row++)
        {
            for(int col = 0; col < width; col++)
                {
                    int count = 0;
                    if( (row - 1) >= 0 && (col - 1) >= 0 && cell[row-1][col-1] == 1)
                        count++;
                    if( (row - 1) >= 0 && cell[row-1][col] == 1)
                        count++;
                    if( (row - 1) >= 0 && (col + 1) < width && cell[row-1][col+1] == 1)
                        count++;
                    if( (col - 1) >= 0 && cell[row][col-1] == 1)
                        count++;
                    if( (col + 1) < width && cell[row][col+1] == 1)
                        count++;
                    if( (row + 1) < height && (col - 1) >= 0 && cell[row+1][col-1] == 1)
                        count++;
                    if( (row + 1) < height && cell[row+1][col] == 1)
                        count++;
                    if( (row + 1) <height && (col + 1) < width  && cell[row+1][col+1] == 1)
                        count++;
                    if(count < 2 || count > 3)
                        temp[row][col] = 0;
                    else if(count == 2)
                        temp[row][col] = cell[row][col];
                    else if(count == 3)
                        temp[row][col] = 1;
                }
        }
        for(int i = 0; i<height; i++)
            for(int j=0; j<width; j++)
                cell[i][j] = temp[i][j];
    }
}

void GameOfLife::display()
{
    system("cls");
    for(int i=0;i<height;i++){
        cout<<endl;
        for(int j=0;j<width;j++)
            if(!cell[i][j])
                cout<<"-";
            else
                cout<<'@';
        }
    cout<<endl<<endl;
}
