CXX = mpicxx
CPPFLAGS = -I/path/to/madness/include
CXXFLAGS = -O3 -g -Wall -fmessage-length=0
LDFLAGS = 
LIBS = -L/path/to/madness/lib -lMADworld

all: axpy reduce fib hello


axpy: axpy.cc Makefile
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $(LIBS) -o axpy axpy.cc

reduce: reduce.cc Makefile
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $(LIBS) -o reduce reduce.cc

fib: fib.cc Makefile
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $(LIBS) -o fib fib.cc

hello: hello.cc Makefile
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $(LIBS) -o hello hello.cc 


clean:
	rm -f axpy reduce fib hello
