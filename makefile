CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
DEP_FILES := $(OBJ_FILES:.o=.d)
CC_FLAGS := -Wall -g -std=c++11 -I include -O2
CPP_TEST_FILES := $(wildcard tests/*.cpp)
EXE_LINK_FLAGS := -L ./lib -lflexium -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

-include obj/$(wildcard *.d)

all: lib/libflexium.a

lib/libflexium.a: $(OBJ_FILES)
	rm $@ -f
	ar -c -rs $@ $^

obj/%.o: src/%.cpp
	g++ -MMD -c -o $@ $< $(CC_FLAGS)

clean:
	rm lib/libflexium.a -f
	rm $(OBJ_FILES) -f
	rm $(DEP_FILES) -f
	rm demo/demo.exe -f
	rm $(wildcard tests/*.exe) -f

demo: lib/libflexium.a demo/Demo.cpp
	g++ demo/Demo.cpp $(CC_FLAGS) -c -o demo/Demo.o
	g++ -o demo/demo.exe demo/Demo.o $(EXE_LINK_FLAGS)

tests: $(CPP_TEST_FILES) $(CPP_TEST_FILES:.cpp=.exe)

tests/%.exe: tests/%.cpp
	g++ -o $@ $< $(CC_FLAGS) $(EXE_LINK_FLAGS)

