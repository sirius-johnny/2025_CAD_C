CC=g++
LDFLAGS=-std=c++14 -O3 -lm
SOURCES=src/main.cpp src/parser.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=bin/cadC
INCLUDES=src/parser.h src/instance.h

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

src/%.o: src/%.cpp $(INCLUDES)
	$(CC) $(LDFLAGS) -c $< -o $@

clean:
	rm -rf src/*.o $(EXECUTABLE)