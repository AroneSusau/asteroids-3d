OS = $(shell uname)

SOURCEDIR = src
BUILDDIR = out
VPATH =  src/main : out/

ifeq ($(OS), Linux)
  VER=c++1y
else
  VER=c++14
endif

CC = g++
CFLAGS = -Wall -std=$(VER) -Wno-deprecated
FRAMEWORK = -Wno-deprecated-declarations -framework GLUT -framework OpenGL -framework Carbon

BASE_OBJECTS = Axis.o Camera.o EulerRotation.o main.o RigidBody.o Ship.o Time.o Wall.o World.o
OBJECTS = $(addprefix out/, $(BASE_OBJECTS))

.default: all

all:
	make clean
	make Asteroid
	./Asteroid

clean:
	if [ $(shell ls out | grep -wv "*.o" -c) -gt 0 ]; then rm $(BUILDDIR)/*.o; fi;
	if [ -f Asteroid ]; then rm Asteroid; fi;

Asteroid: $(BASE_OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o Asteroid $(FRAMEWORK)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $(BUILDDIR)/$@
	