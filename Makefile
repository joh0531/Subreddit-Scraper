CXX = g++
CXXFLAGS = -g -gdwarf-2 -Wall -std=gnu++11
LD= g++
LDFLAGS=
AR= ar
ARFLAGS= rc

LIBRARY= libmap.a
LIB_SRC= constants.cpp rbtree.cpp treap.cpp bst.cpp

LIB_OBJ= $(LIB_SRC:.cpp=.o)

PROGRAMS: store_reddit

all: 	$(LIBRARY) $(PROGRAMS)

rbtree.o:	rbtree.cpp map.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

bst.o:	bst.cpp map.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

treap.o:	treap.cpp map.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

store_reddit.o: store_reddit.cpp map.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

constants.o: constants.cpp map.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(LIBRARY): $(LIB_OBJ)
	$(AR) $(ARFLAGS) $@ $(LIB_OBJ)

store_reddit: store_reddit.o map.h $(LIBRARY)
	$(LD) $(LDFLAGS) -o $@ $< $(LIBRARY) 

clean:
	rm -f $(LIBRARY) $(PROGRAMS) *.o
