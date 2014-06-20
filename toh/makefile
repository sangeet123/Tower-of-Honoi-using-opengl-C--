CPP = g++
CFLAGS = -lGL -lGLU -lglut -lpthread -Wall -lm
OFLAG = -o
.SUFFIXES : .o .cpp
.cpp.o :
	$(CPP) $(CPPFLAGS) -c $<

toh: main.o display_func.o
	$(CPP) $(OFLAG) toh main.o display_func.o $(CFLAGS)

clean:
	$(RM) *.o
