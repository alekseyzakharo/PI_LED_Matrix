## Compiler Info + Flags
#CC_ARM = arm-linux-gnueabihf-g++
#CFLAGS = -O3 -g3 -Wall -fPIC
#
## when building directory use this
#SRC_DIR = /home/$USER/pi/work/ledMatrix
#OBJ_DIR = /home/$USER/pi/work/ledMatrix
#
#SRC_FILES =$(wildcard *.cpp)
#OBJ_FILES =$(patsubst %.cpp,%.o,$(SRC_FILES))
#
## Build Target
#TARGET = ledmatrix.out
#
## Shared Directory Path
#SHARE_PATH = $(HOME)/pi/public/
#
## Default All
#all: compile_target copy_target clean
#
## Compile Targets
#compile_target: main.o gpio.o
##	$(CC_ARM) $(CFLAGS) -o $(OBJ_FILES) $(SRC_FILES)
#	$(CC_ARM) main.o gpio.o -o $(TARGET)
#
#main.o: main.cpp
#	$(CC_ARM) $(CFLAGS) main.cpp
#	
#gpio.o: gpio.cpp
#	$(CC_ARM) $(CFLAGS) GPIO.cpp
#
## Copy Targetsarm-linux-gnueabihf-g++ -O3 -g3 -Wall -fPIC
#copy_target:
#	cp $(TARGET) $(SHARE_PATH)
#
## Clean-Up
#clean:
#	rm -f *.o $(TARGET)

CC := arm-linux-gnueabihf-g++
CFLAGS := -O3 -g3 -Wall -fPIC
TARGET := ledmatrix.out

SHARE_PATH = $(HOME)/pi/public/

# $(wildcard *.cpp /xxx/xxx/*.cpp): get all .cpp files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard *.cpp)
# $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

all: $(TARGET) copy_target clean
$(TARGET): $(OBJS)
	$(CC) -o $@ $^
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
	
copy_target:
	cp $(TARGET) $(SHARE_PATH)

clean:
	rm -rf $(TARGET) *.o
	

