CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-O2 -Wall -Wextra -pedantic
LDFLAGS=-O2 -Wall -Wextra -pedantic
LDLIBS=$(shell root-config --libs)

SRCS=main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: glicko

glicko: $(OBJS)
	$(CXX) $(LDFLAGS) -o glicko $(OBJS) $(LDLIBS) 

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .depend

include .depend
