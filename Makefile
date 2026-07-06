CXX=g++
CXXFLAGS=-Wall -Werror -g

.PHONY:
all: demo

.PHONY:
clean:
	-rm -f demo *.o

demo: main.o
	$(CXX) $(CXXFLAGS) -o demo $^

.cc.o:
	$(CXX) $(CXXFLAGS) -c $<

