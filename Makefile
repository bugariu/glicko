CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-std=c++14 -O2 -Wall -Wextra -pedantic
LDFLAGS=-std=c++14 -O2 -Wall -Wextra -pedantic
LDLIBS=

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

distclean: clean
	$(RM) *~ .depend
	$(RM) glicko

include .depend
