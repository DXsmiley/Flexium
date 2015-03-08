# Makefile for gcc.
# You'll probably have to adjust it to fit your own needs, depending on where you installed Flexium

FLEXIUM_PATH := ../Flexium/
CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(CPP_FILES:.cpp=.o)
LD_FLAGS := -L $(FLEXIUM_PATH)lib -lFlexium -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio
CC_FLAGS := -MMD -Wall -g -std=c++11 -I $(FLEXIUM_PATH)include -O2

subsystem:
	$(MAKE) -C ../Flexium/
	$(MAKE) all

all: main.exe $(OBJ_FILES)

-include $(OBJ_FILES:.o=.d)

main.exe: $(OBJ_FILES) ../Flexium/lib/libflexium.a
	g++ -o $@ $(OBJ_FILES) $(LD_FLAGS)

%.o: %.cpp
	g++ -c -o $@ $< $(CC_FLAGS) 

clean:
	rm -f $(OBJ_FILES)
