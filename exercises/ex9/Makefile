# Copyright ©2024 Alex Hansen.  All rights reserved. No use, copying, 
# distribution, or modification is permitted without prior written consent.
# Copyrights for third-party components of this work must be honored.
# 
# ahansen4@uw.edu

CXX = g++
CPPFLAGS = -Wall -g -std=c++17

# default target to build all executables
all: ex9

ex9: Vector.o ex9.o
	$(CXX) $(CPPFLAGS) -o $@ $^

ex9.o: ex9.cc Vector.h
	$(CXX) $(CPPFLAGS) -c $<

Vector.o: Vector.cc Vector.h
	$(CXX) $(CPPFLAGS) -c $<

clean:
	rm -rf *.o *~ *.dSYM ex9
