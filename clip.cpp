#include <iostream>
#include "inp.h"
#include "draw.h"
#include "clip.h"
#include <GL/glut.h>

using namespace std;

int temparr[20][2]; //USing temporary array to store new vertices.
int new_arrsize;

int x_int(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) // Function to calc the dot prod of the x-intersection btwn clipper edge and polygon line.
{
  int num = (x1*y2 - y1*x2)*(x3-x4) - (x1-x2)*(x3*y4 - y3*x4);
  int den = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
  return int(num/den);
}

int y_int(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) // Function to calc dot prod of the y-intersection btwn clipper edge and polygon line.
{
  int num = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4 - y3*x4);
  int den = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
  return int(num/den);
}

int clip(int cnt, int arr[][2], int x1, int y1, int x2, int y2)  //function that computes the position of the points w.r.t clipper edge.
{
  new_arrsize = 0;
  for(int i = 0; i < cnt; ++i)
  {
    int a = (i + 1)%(cnt);
    int pos_i = (x2 - x1)*(arr[i][1] - y1) - (y2 - y1)*(arr[i][0] - x1);  //calc position of 1st point wrt clipper edge
    int pos_a = (x2 - x1)*(arr[a][1] - y1) - (y2 - y1)*(arr[a][0] - x1);  //calc position of 2nd point wrt clipper edge

  //  4 cases for handling clipping.

    if(pos_i < 0 && pos_a < 0)  // Case 1 - Both points of input polygon inside.
    {
      //  adding only 2nd vertex of polygon edge.
      temparr[new_arrsize][0] = arr[a][0];
      temparr[new_arrsize][1] = arr[a][1];
      new_arrsize += 1;
    }
    else if(pos_i >= 0 && pos_a < 0)  // Case 2 - Only first point outside.
    {
      //  adding intersection vertex and 2nd vertex.
      temparr[new_arrsize][0] = x_int(x1, y1, x2, y2, arr[i][0], arr[i][1], arr[a][0], arr[a][1]);
      temparr[new_arrsize][1] = y_int(x1, y1, x2, y2, arr[i][0], arr[i][1], arr[a][0], arr[a][1]);
      new_arrsize += 1;
      temparr[new_arrsize][0] = arr[a][0];
      temparr[new_arrsize][1] = arr[a][1];
      new_arrsize += 1;
    }
    else if(pos_i < 0 && pos_a >= 0)  //  Case 3 - Only 2nd point outside.
    {
      //  adding only intersection vertex.
      temparr[new_arrsize][0] = x_int(x1, y1, x2, y2, arr[i][0], arr[i][1], arr[a][0], arr[a][1]);
      temparr[new_arrsize][1] = y_int(x1, y1, x2, y2, arr[i][0], arr[i][1], arr[a][0], arr[a][1]);
      new_arrsize += 1;
    }
    else  //  Both points outside.
      continue;

  }

  cnt = new_arrsize;
  for(int i = 0; i < cnt; ++i) //Copying to original array.
  {
    arr[i][0] = temparr[i][0];
    arr[i][1] = temparr[i][1];
  }
  return cnt;
}
