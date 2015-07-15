RGB_INCDIR= ../matrix_library/include
RGB_LIBDIR= ../matrix_library/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread

CXX := g++
CXXFLAGS := -Wall -O3 -g -std=c++0x
OBJECTS := pong.o game.o
BINARIES := pong_bin

pong.app : $(OBJECTS) $(RGB_LIBRARY)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)


# (FYI: Make sure, there is a TAB-character in front of the $(MAKE))
$(RGB_LIBRARY):
	$(MAKE) -C $(RGB_LIBDIR)

pong.o : pong.cpp pong.h game.h
	$(CXX) $(CXXFLAGS) -I$(RGB_INCDIR)  pong.cpp -c -o  $@
game.o : game.h game.cpp
		$(CXX) $(CXXFLAGS) -I$(RGB_INCDIR)  game.cpp -c -o  $@
