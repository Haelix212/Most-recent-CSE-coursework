# Copyright ©2024 Alex Hansen.  All rights reserved. No use, copying, 
# distribution, or modification is permitted without prior written consent.
# Copyrights for third-party components of this work must be honored.
# Modified from Hal Perkins' exercise 9 sample solution.
#
# ahansen4@uw.edu

CXX = g++
OBJS = Vector.o ex10.o
EXE  = ex10
HEADERS = Vector.h
CPPFLAGS = -Wall -g -std=c++17

# default target
$(EXE): $(OBJS)
	$(CXX) $(CPPFLAGS) -o $(EXE) $(OBJS)

# source files
%.o: %.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) -c $<

# phony target - remove generated files and backups
clean:
	rm -rf $(EXE) *.o *~ *.dSYM
