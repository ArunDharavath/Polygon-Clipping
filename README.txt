ABOUT PROGRAM:
  The program MAIN.CPP checks if the number of commandline arguments given and proceeds accordingly.
  It contains calls to input function and draw function defined in INP.CPP and DRAW.CPP.

  INP.CPP program contains the functionality to work with input files.

  DRAW.CPP program deals with drawing the calling the clip function in CLIP.CPP.
  After this, it draws the clipped polygon and fills it using the scanfill function from SCANFILL.CPP. Code has been commented for filling the polygon using in-built gl-function.
  The program, then draws the clipper polygon.

  CLIP.CPP clips the input polygon wrt clipper polygon edges.

  SCANFILL.cpp fills the clipped polygon accordingly.


GUIDELINES:
  If there are comments in the beginning of the input file, please mention the number of vertices and the coordinates in the following manner:
  #
  no. of vertices       //This should come right after the last comment in the continuous sequence of comments from the beginning, without an empty line
  x1 y1
  x2 y2
  x3 y3
  x4 y4

  no. of vertices of input POLYGON
  x1 y1
  .
  .
  .

  Otherwise, if there are no comments, please follow the following format:
  no. of vertices       //This should come at the first line of the input file and the below should follow.
  x1 y1
  x2 y2
  x3 y3
  x4 y4

  no. of vertices of input POLYGON
  x1 y1
  .
  .
  .

  For more clarity, I have included a test input file INPUT.DAT, in my tar file.

  The program can be compiled by changing the directory to the tar file name, and executing the command 'make', from the commandline.
  After this, execute "./prog inp_file" where the input file's name is to be entered in place of inp_file.
  
  
REFERENCES:
  1. Clipping ppt
  2. Youtube video   url: https://www.youtube.com/watch?v=Euuw72Ymu0M
  3. I have used GeeksforGeeks to get a better understanding of the algorithm and to use the code and modify it according to my program and understanding.  url: https://www.geeksforgeeks.org/polygon-clipping-sutherland-hodgman-algorithm-please-change-bmp-images-jpeg-png/
