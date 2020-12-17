#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void newRange(int& min, int& max, char a); //Set's new min or max for row & column depending on character

struct mySeat{
  int row;
  int column;
};

mySeat findMySeat(bool seatsFull[][8]);

int main()
{
  ifstream inputObject1("input.txt");
  string input1;

  int highSeatId{};
  mySeat seat{};

  bool seatsFull[128][8]{};

  //min and max to find row
  int min{0};
  int max{127};

  //min and max to find column
  int minc{0};
  int maxc{7};

  //final row and column for "neatness"
  int row{0};
  int column{0};

  while(inputObject1 >> input1)
  {
    //Resets min, max
    min=0;
    max=127;

    minc=0;
    maxc=7;

    //chunk finds the row
    for(int i=0; i<7; ++i)
    {
      newRange(min, max, input1[i]);
    }
    row=min;

    //chunk finds the column
    for(int i=7; i<10; ++i)
    {
      newRange(minc, maxc, input1[i]);
    }
    column=minc;

    //chunk does part a
    if((row*8+column)>highSeatId)
    {
      highSeatId=row*8+column;
    }

    //sets seats as full
    for(int i=0; i<128; ++i)
    {
      for(int j=0; j<8; ++j)
      {
        seatsFull[row][column]=true;
      }
    }
  }

  seat=findMySeat(seatsFull);

  cout << highSeatId << endl;
  cout << seat.row*8+seat.column << endl;

  return 0;
}

void newRange(int& min, int& max, char a)
{
  if(a=='F' || a=='L')
  {
    max=max-(max-min+1)/2;
  }
  else
  {
    min=(max-min+1)/2+min;
  }
  return;
}

mySeat findMySeat(bool seatsFull[][8])
{
  mySeat seat{};
  for(int i=1; i<127; ++i)
  {
    for(int j=0; j<8; ++j)
    {
      if(seatsFull[i][j]==false)
      {
        if(seatsFull[i-1][j]==true && seatsFull[i+1][j]==true && seatsFull[i][j-1]==true && seatsFull[i][j+1]==true)
        {
          seat.row=i;
          seat.column=j;
        }
      }
    }
  }
  return seat;
}