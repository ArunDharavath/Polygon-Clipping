#include <iostream>
#include <cstdio>
#include "inp.h"

using namespace std;

int vert_lcount;//var used to count number of vertices of all polygons.
int polycounter;//counts nuymber of polygons in input files.
int vert[1000][2];//stores vertices of all polygons.
int vertcount[100];//stores the number of vertices for each polygon.
float poly_color[100][3];//stores rgb values of each polygon.
int clipper[10][2], clip_vert;

void read_inp(char *fname)
{
  FILE *f;
  f = fopen(fname, "r");
  int i = 0;
  vert_lcount = 0;
  polycounter=0;
  char temp[90];

  fgets(temp, 90, f);

  while(true)//Check if commented line.
  {
    if(temp[0] == '#')
      fgets(temp, 90, f);
    else
      break;
  }
  sscanf(temp, "%d", &clip_vert);//take as input the number vertices of clipper polygon.

  for(int a = 0; a < clip_vert; ++a)//take input of clipper polygon vertices.
  {
    fgets(temp, 90, f);
    if(temp[0] == '#')
    {
      a -= 1;
      continue;
    }
    sscanf(temp, "%d %d", &clipper[a][0], &clipper[a][1]);
  }

  while(true)//reading input from input file.
  {
    fgets(temp, 90, f);
    if(temp[0] == '#')//check for comments in input file.
      continue;

    if(feof(f))
      break;
      
    fgets(temp, 90, f);

    if(temp[0] != '\n')
    {
      sscanf(temp, "%d %f %f %f", &vertcount[i], &poly_color[i][0], &poly_color[i][1], &poly_color[i][2]);
      polycounter++;
      int j = 0;

      for(j = vert_lcount; j < (vert_lcount+vertcount[i]); ++j)
      {
        fgets(temp, 90, f);
        if(temp[0] == '#')
        {//check for comments in input file.
          j -= 1;
          continue;
        }
        if(temp[0] != '\n')
        {
          sscanf(temp, "%d %d", &vert[j][0], &vert[j][1]);
        }
        else
        {
          j -= 1;
        }
      }
      vert_lcount += vertcount[i];
      i += 1;
    }
  }
  fclose(f);
}
