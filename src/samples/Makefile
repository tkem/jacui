#-*-Makefile-*-

CC = gcc
CXX = g++

CFLAGS = -g -O2 -I../include
LDFLAGS = -lSDL_ttf -lSDL_image -lSDL

PROGRAMS = imgview fontview

SRCS = imgview.cpp fontview.cpp icons.cpp vera.cpp

OBJS = icons.o vera.o

LIBS = ../libjacui.a

all: $(PROGRAMS)

imgview: imgview.o $(OBJS) $(LIBS)
	$(CXX) -o $@ $+ $(LDFLAGS)

fontview: fontview.o $(OBJS) $(LIBS)
	$(CXX) -o $@ $+ $(LDFLAGS)

clean:
	rm -f $(PROGRAMS) *.o .depend *~

depend: .depend

.SUFFIXES:
.SUFFIXES: .c .cpp .o

.depend: $(SRCS)
	$(CXX) $(CFLAGS) -MM $+ > $@

.cpp.o:
	$(CXX) $(CFLAGS) -o $@ -c $<

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

include .depend
