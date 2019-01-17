CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

LIBRARIES	:= -lSDL2
EXECUTABLE	:= playground

all: $(EXECUTABLE)

$(EXECUTABLE): src/*.cpp
	$(CXX) $(CXX_FLAGS) $^ -o $@ $(LIBRARIES)

clean:
	rm -rf $(EXECUTABLE)
