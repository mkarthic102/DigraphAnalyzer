# Makefile
CPP=g++
CPPFLAGS=-std=c++11 -Wall -Wextra -pedantic -g
                                                                             
# Links files together to create executable                                                                                                                 
digraph_analyzer: digraph_analyzer.o
	$(CPP) -o digraph_analyzer digraph_analyzer.o

# Creates object files                                                                                                                                                               
digraph_analyzer.o: digraph_analyzer.cpp digraph_functions.h
	$(CPP) $(CPPFLAGS) -c digraph_analyzer.cpp

# Removes all object files and the executables so we can start fresh                                                                                                                                                              
clean:
	rm -f *.o digraph_analyzer