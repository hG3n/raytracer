# -*- Mode:Makefile -*-

CXX		=g++-4.9

# on MACOS 64 Bit
CXXFLAGS	=-g -O1 -fPIC -W -Wall -m64
#CXXFLAGS	=-g -O1 -fPIC -W -Wall

CXXINCLUDE	=-I.
CXXDEFINES	=
LDXXFLAGS	=$(CXXFLAGS) -L. -fPIC -Wl,-rpath,.
RM		=rm -f
