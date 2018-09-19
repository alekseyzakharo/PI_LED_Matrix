# Compiler Info + Flags
CC_ARM = arm-linux-gnueabihf-g++
CFLAGS = -O3 -g3 -Wall -fPIC -c

# when building directory use this
SRC_DIR = /home/$USER/pi/work/ledMatrix
OBJ_DIR = /home/$USER/pi/work/ledMatrix

SRC_FILES =$(wildcard *.cpp)
OBJ_FILES =$(patsubst %.cpp,%.o,$(SRC_FILES))

# Build Target
TARGET = ledmatrix.out

# Shared Directory Path
SHARE_PATH = $(HOME)/pi/public/

# Default All
all: compile_target copy_target clean

# Compile Targets
compile_target:
	$(CC_ARM) $(CFLAGS) -o $(OBJ_FILES) $(SRC_FILES)
	$(CC_ARM) -o $(TARGET) $(OBJ_FILES)

# Copy Targets
copy_target:
	cp $(TARGET) $(SHARE_PATH)

# Clean-Up
clean:
	rm -f *.o $(TARGET)

