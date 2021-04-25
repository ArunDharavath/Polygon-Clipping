#include <iostream>
#include <GL/glut.h>
#include "draw.h"
#include "inp.h"
#include "scanfill.h"

typedef struct edgebucket
{
  int ymax;
  float xofymin;
  float slopeinverse;
}EdgeBucket;

typedef struct edgetabletup
{
  int countEdgeBucket;
  EdgeBucket buckets[vert_max];
}EdgeTableTuple;

EdgeTableTuple EdgeTable[h_max], ActiveEdgeTuple;

void initedgetable(int max_y)
{
  int i;
  for (i = 0; i < max_y; ++i)
    EdgeTable[i].countEdgeBucket = 0;

  ActiveEdgeTuple.countEdgeBucket = 0;
}

void insertionSort(EdgeTableTuple *ett)
{
  int i,j;
  EdgeBucket temp;

  for (i = 1; i < ett->countEdgeBucket; i++)
  {
    temp.ymax = ett->buckets[i].ymax;
    temp.xofymin = ett->buckets[i].xofymin;
    temp.slopeinverse = ett->buckets[i].slopeinverse;
    j = i - 1;

    while ((temp.xofymin < ett->buckets[j].xofymin) && (j >= 0))
    {
      ett->buckets[j + 1].ymax = ett->buckets[j].ymax;
      ett->buckets[j + 1].xofymin = ett->buckets[j].xofymin;
      ett->buckets[j + 1].slopeinverse = ett->buckets[j].slopeinverse;
      j = j - 1;
    }
    ett->buckets[j + 1].ymax = temp.ymax;
    ett->buckets[j + 1].xofymin = temp.xofymin;
    ett->buckets[j + 1].slopeinverse = temp.slopeinverse;
  }
}

void storeEdgeInTuple(EdgeTableTuple *receiver, int ym, int xm, float slopInv)
{
  (receiver->buckets[(receiver)->countEdgeBucket]).ymax = ym;
  (receiver->buckets[(receiver)->countEdgeBucket]).xofymin = (float)xm;
  (receiver->buckets[(receiver)->countEdgeBucket]).slopeinverse = slopInv;

  insertionSort(receiver);
  (receiver->countEdgeBucket)++;
}

int storeEdgeInTable(int x1, int y1, int x2, int y2)
{
  float m, inv_m;
  int ymaxTS,xwithyminTS, scanline; //ts stands for to store
  if (x2 == x1)
  {
    inv_m = 0.000000;
  }
  else
  {
    m = ((float)(y2-y1))/((float)(x2-x1));

    // horizontal lines are not stored in edge table
    if (y2==y1)
      return 0;

    inv_m = (float)1.0/m;
  }

  if(y1>y2)
  {
    scanline=y2;
    ymaxTS=y1;
    xwithyminTS=x2;
  }
  else
  {
    scanline=y1;
    ymaxTS=y2;
    xwithyminTS=x1;
  }
  // the assignment part is done..now storage..
  storeEdgeInTuple(&EdgeTable[scanline],ymaxTS,xwithyminTS,inv_m);
  return 0;
}

void removeEdgeByYmax(EdgeTableTuple *Tup,int yy)
{
  int i,j;
  for(i=0; i < Tup->countEdgeBucket; ++i)
  {
    if(Tup->buckets[i].ymax == yy)
    {
      for ( j = i ; j < Tup->countEdgeBucket -1 ; j++ )
      {
        Tup->buckets[j].ymax =Tup->buckets[j+1].ymax;
        Tup->buckets[j].xofymin =Tup->buckets[j+1].xofymin;
        Tup->buckets[j].slopeinverse = Tup->buckets[j+1].slopeinverse;
      }
      Tup->countEdgeBucket--;
      i--;
    }
  }
}

void updatexbyslopeinv(EdgeTableTuple *Tup)
{
  int i;

  for (i=0; i<Tup->countEdgeBucket; ++i)
  {
    (Tup->buckets[i]).xofymin =(Tup->buckets[i]).xofymin + (Tup->buckets[i]).slopeinverse;
  }
}

void ScanlineFill(int max_y, float f1, float f2, float f3)
{

  int i, j, x1, ymax1, x2, ymax2, FillFlag = 0, coordCount;

  for(i=0; i < max_y; i++)//4. Increment y by 1 (next scan line)
  {

    for (j=0; j<EdgeTable[i].countEdgeBucket; j++)
    {
      storeEdgeInTuple(&ActiveEdgeTuple, EdgeTable[i].buckets[j].ymax, EdgeTable[i].buckets[j].xofymin, EdgeTable[i].buckets[j].slopeinverse);
    }


    removeEdgeByYmax(&ActiveEdgeTuple, i);

    insertionSort(&ActiveEdgeTuple);

    //3. Fill lines on scan line y by using pairs of x-coords from AET
    j = 0;
    FillFlag = 0;
    coordCount = 0;
    x1 = 0;
    x2 = 0;
    ymax1 = 0;
    ymax2 = 0;
    while(j<ActiveEdgeTuple.countEdgeBucket)
    {
      if(coordCount%2==0)
      {
        x1 = (int)(ActiveEdgeTuple.buckets[j].xofymin);
        ymax1 = ActiveEdgeTuple.buckets[j].ymax;
        if(x1==x2)
        {
          if (((x1==ymax1)&&(x2!=ymax2))||((x1!=ymax1)&&(x2==ymax2)))
          {
            x2 = x1;
            ymax2 = ymax1;
          }
          else
            coordCount++;
        }
        else
        {
          coordCount++;
        }
      }
      else
      {
        x2 = (int)ActiveEdgeTuple.buckets[j].xofymin;
        ymax2 = ActiveEdgeTuple.buckets[j].ymax;
        FillFlag = 0;
        // checking for intersection...
        if (x1==x2)
        {

          if (((x1==ymax1)&&(x2!=ymax2))||((x1!=ymax1)&&(x2==ymax2)))
          {
            x1 = x2;
            ymax1 = ymax2;
          }
          else
          {
            coordCount++;
            FillFlag = 1;
          }
        }
        else
        {
          coordCount++;
          FillFlag = 1;
        }
        if(FillFlag)
        {
          //drawing actual lines...
          glColor3f(f1, f2, f3);
          glBegin(GL_LINES);
            glVertex2i(x1,i);
            glVertex2i(x2,i);
          glEnd();
          glFlush();

        }
      }
      j++;
    }

    updatexbyslopeinv(&ActiveEdgeTuple);
  }
}
