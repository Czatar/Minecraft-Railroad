# Makefile designed for a Unix-like OS
# Given "coors.txt", the "make" command is enough to output into "result.txt"

CXX = g++
CXXFLAGS = -Wall -std=c++17
OBJS = main.o
FILE = coords.txt

all: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o output.out
	./output.out $(FILE)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#

val:
	valgrind ./output.out $(FILE)

run:
	./output.out $(FILE)
