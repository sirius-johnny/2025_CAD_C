CC = g++
LDFLAGS = -std=c++17 -O3 -lm
SRCDIR = src
INCLUDES = -I$(SRCDIR)

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(SRCDIR)/%.o, $(SOURCES))

EXECUTABLE = bin/cadC

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(LDFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(SRCDIR)/*.o $(EXECUTABLE)
