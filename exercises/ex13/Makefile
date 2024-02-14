# Copyright ©2024 Alex Hansen.  All rights reserved. No use, copying, 
# distribution, or modification is permitted without prior written consent.
# Copyrights for third-party components of this work must be honored.
# 
# ahansen4@uw.edu

CXX = g++
CPPFLAGS = -Wall -g -std=c++17

# default target to build all executables
all: ex13

ex13: Cartesian.o Polar.o ex13.o
	$(CXX) $(CPPFLAGS) -o $@ $^

ex13.o: ex13.cc 
	$(CXX) $(CPPFLAGS) -c $<

Cartesian.o: Cartesian.cc Cartesian.h Coordinate.h
	$(CXX) $(CPPFLAGS) -c $<

Polar.o: Polar.cc Polar.h Coordinate.h
	$(CXX) $(CPPFLAGS) -c $<

clean:
	rm -rf *.o *~ ex13
