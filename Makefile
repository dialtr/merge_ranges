CXX=g++
CXXFLAGS=-std=c++20 -Wall -Werror -g

.PHONY:
all: demo

.PHONY:
clean:
	-rm -f demo *.o

demo: main.o
	$(CXX) $(CXXFLAGS) -o demo $^

.PHONY:
format:
	clang-format -style=Google -i *.cc

.cc.o:
	$(CXX) $(CXXFLAGS) -c $<

