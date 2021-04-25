OBJS	= main.o inp.o draw.o clip.o scanfill.o
SOURCE	= main.cpp inp.cpp draw.cpp clip.cpp scanfill.cpp
HEADER	= inp.h draw.h clip.h scanfill.h
OUT	= prog
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -lglut -lGLU -lGL -lm

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

inp.o: inp.cpp
	$(CC) $(FLAGS) inp.cpp

draw.o: draw.cpp
	$(CC) $(FLAGS) draw.cpp

clip.o: clip.cpp
	$(CC) $(FLAGS) clip.cpp

scanfill.o: scanfill.cpp
	$(CC) $(FLAGS) scanfill.cpp
