#include <iostream>
#include "inp.h"
#include "draw.h"
using namespace std;

int main(int argc, char** argv)
{
  if(argc == 2)//takes in only executable and input filenames.
  {
    read_inp(argv[1]);//execs the input function in inp.cpp
    draw(argc, argv);//execs the draw func in draw.cpp
    return 0;
  }
  else if(argc < 2)
  {
    cout << endl << "Please provide both EXECUTABlE and INPUT filename." << endl << endl;
    return -1;
  }
  else
  {
    cout << endl << "Please provide only EXECUTABLE filename and INPUT filename." << endl << endl;
    return -1;
  }
}
