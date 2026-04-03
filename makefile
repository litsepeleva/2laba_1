CXX = g++
CXXFLAGS = -Wall -std=c++11
all: meb
	./meb
meb: main.o meb.o
	$(CXX) $(CXXFLAGS) main.o meb.o -o meb
main.o: main.cpp meb.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp
meb.o: meb.cpp meb.hpp
	$(CXX) $(CXXFLAGS) -c meb.cpp
clean:
	rm -f meb *.o
