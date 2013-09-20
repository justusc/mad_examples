CXX = mpicxx
CPPFLAGS = -I/path/to/madness/include
CXXFLAGS = -O3 -g -Wall -fmessage-length=0
LDFLAGS = -L/path/to/madness/lib
LIBS = -lMADworld

all: axpy reduce fib fast_fib


axpy: axpy.cc Makefile
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $(LIBS) -o axpy axpy.cc

reduce: reduce.cc Makefile
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $(LIBS) -o reduce reduce.cc

fib: fib.cc Makefile
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $(LIBS) -o fib fib.cc

fast_fib: fast_fib.cc Makefile
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $(LIBS) -o fast_fib fast_fib.cc 


clean:
	rm -f axpy reduce fib fast_fib
