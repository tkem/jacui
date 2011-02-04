#-*-Makefile-*-

AR = ar rcs
CC = gcc
CXX = g++
TAR = tar --exclude=.depend

CFLAGS = -g -O2 -I../include

LIBNAME = libjacui

LIB = ../$(LIBNAME).a

SRCS =	canvas.cpp colors.cpp cursor.cpp cursors.cpp detail.cpp \
	event.cpp error.cpp font.cpp image.cpp surface.cpp \
	types.cpp window.cpp xpmicon.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(LIB)

$(LIB): $(OBJS)
	$(AR) $@ $+

clean:
	rm -f $(LIB) *.o .depend *~

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
