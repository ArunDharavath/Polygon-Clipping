#include <iostream>
#include <GL/glut.h>
#include "inp.h"
#include "draw.h"
#include "clip.h"
#include "scanfill.h"

using namespace std;

void init() //additional necessary initialisations
{

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w_max, 0, h_max);
    glClear(GL_COLOR_BUFFER_BIT);
}

void drawpolygon()  //actual function that draws the polygon.
{
  int i, j, temp = 0;
  int arr[20][2];

  int max_y = -1, count, x1, y1, y2, x2;

  for(i = 0; i < polycounter; ++i)  //calling clip function for each polygon.
  {
    int cnt = 0;
    for(int k = temp; k < (temp+vertcount[i]); ++k) //creating another array to store the new clipped edges.
    {
      arr[cnt][0] = vert[k][0];
      arr[cnt][1] = vert[k][1];
    //  cout << arr[cnt][0] << " " << arr[cnt][1] << endl;
      cnt++;
    }
  //  cout << endl;
    temp += vertcount[i];


    for(j = 0; j < clip_vert; ++j)  //Send as parameters one edge of the clipper in clockwise manner.
    {
      int b = (j+1)%clip_vert;
      cnt = clip(cnt, arr, clipper[j][0], clipper[j][1], clipper[b][0], clipper[b][1]);
    }


    /*glColor3f(poly_color[i][0], poly_color[i][1], poly_color[i][2]);
    glBegin(GL_POLYGON);
    for(int k = 0; k < cnt; ++k)  //draw the new clipped edges of the polygon.
    {
      int x = (k+1)%cnt;
      glVertex2i(arr[k][0], arr[k][1]);
      glVertex2i(arr[x][0], arr[x][1]);
    }
    glEnd();
    glFlush();*/


    max_y= -1;
    count = 0;
    int xinit, yinit = 0;
    glBegin(GL_LINE_LOOP);
    glColor3f(poly_color[i][0], poly_color[i][1], poly_color[i][2]);
    for(j = 0; j < cnt; ++j)//to draw line segments from one vertex to its consecutive one, and so on.
    {
      if(s[0] != '\n')
      {
        count++;
        if(count>2)
        {
           x1 = x2;
	         y1 = y2;
	         count = 2;
	      }
        if(count == 1)
        {
          x1 = arr[j][0];
          y1 = arr[j][1];
          if(j == 0)
          {
            xinit = x1;
            yinit = y1;
          }
          if(max_y < y1)
          {
            max_y = y1;
          }
          glVertex2i(x1, y1);
        }
        else
        {
          x2 = arr[j][0];
          y2 = arr[j][1];
          if(max_y < y2)
          {
            max_y = y2;
          }
          glVertex2i(x2, y2);
          storeEdgeInTable(x1, y1, x2, y2);
          if(j == (cnt - 1))
          {
				    storeEdgeInTable(xinit, yinit, x2, y2);
			    }
        }
      }
    }
    glEnd();
    glFlush();
    ScanlineFill(max_y, poly_color[i][0], poly_color[i][1], poly_color[i][2]);
    initedgetable(max_y);

  }


  glColor3f(0.0f,0.0f,0.0f);
  glBegin(GL_LINES);
  for(i = 0; i < clip_vert; ++i)  //drawing the clipper polygon.
  {
    //cout << clipper[i][0] << " " << clipper[i][1] << endl;
    int k = (i+1)%clip_vert;
    glVertex2i(clipper[i][0], clipper[i][1]);
    glVertex2i(clipper[k][0], clipper[k][1]);
  }
  ///cout << endl;
  glEnd();
  glFlush();

}

void draw(int num, char **s)  //window attributes are defined.
{
  glutInit(&num, s);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(w_max, h_max);
  glutInitWindowPosition(500, 150);
  glutCreateWindow("Scanline drawn POLYGON");
  init();
  glutDisplayFunc(drawpolygon);
  glutMainLoop();
}
