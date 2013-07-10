# -*- Mode:Makefile -*-

CXX		=g++

# on MACOS 64 Bit
#CXXFLAGS	=-g -O1 -fPIC -W -Wall -m64
CXXFLAGS	=-g -O1 -fPIC -W -Wall

CXXINCLUDE	=-I.
CXXDEFINES	=
LDXXFLAGS	=$(CXXFLAGS) -L. -fPIC -Wl,-rpath,.
RM		=rm -f
