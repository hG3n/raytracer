# -*- Makefile -*-

default: targets

UNAME := $(shell uname -s)

prefix =.

include $(prefix)/defines.mk

CXX = g++ -std=c++0x

CXXINCLUDE	+=-I$(prefix)/include -I/opt/local/include
ifeq ($(UNAME), Darwin)
LIBS		+=-framework OpenGL -framework GLUT

else
LIBS		+=-lglut -lGL
endif

EXTRA_LIBS	+=-L$(prefix)/ -Wl,-rpath,. -L/opt/local/lib
MOVE		=mv

HEADER =\
	include/glutwindow.hpp \
	include/pixel.hpp \
	include/ppmwriter.hpp \
	include/color.hpp \
	include/vector.hpp \
	include/point.hpp \
	include/matrix.hpp \
        $(NULL)

SOURCE =\
	src/glutwindow.cpp \
	src/pixel.cpp \
	src/ppmwriter.cpp \
	src/color.cpp \
	src/point.cpp \
	src/vector.cpp \
	src/matrix.cpp \
	src/main.cpp \
	$(NULL)

OBJECTS =$(SOURCE:.cpp=.o) 

PROGRAMS = 	main

targets:	$(PROGRAMS)

$(PROGRAMS):	$(OBJECTS)
	$(CXX) -o ./$@ $(OBJECTS) $(LIBS) $(EXTRA_LIBS) $(LDXXFLAGS)

realclean:: clean
	-$(RM) $(prefix)/$(OBJECTS)
	-$(RM) $(prefix)/$(PROGRAMOBJECTS)
	-$(RM) $(prefix)/$(PROGRAMS)

include $(prefix)/rules.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),realclean)
#-include $(OBJECTS:.o=.d)
endif
endif
