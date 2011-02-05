# Process this file with automake to produce Makefile.in

# Make sure that when we re-make ./configure, we get the macros we need
# ACLOCAL_AMFLAGS = -I m4

# This is so we can #include <jacui/foo.hpp>
AM_CPPFLAGS = -I$(top_srcdir)/src

# This is mostly based on configure options
AM_CXXFLAGS =

AUTOMAKE_OPTIONS = subdir-objects

lib_LTLIBRARIES = libjacui.la

libjacui_la_SOURCES = \
	src/sdl1.2/canvas.cpp \
	src/sdl1.2/cursor.cpp \
	src/sdl1.2/cursors.cpp \
	src/sdl1.2/detail.cpp \
	src/sdl1.2/detail.hpp \
	src/sdl1.2/error.cpp \
	src/sdl1.2/event.cpp \
	src/sdl1.2/font.cpp \
	src/sdl1.2/image.cpp \
	src/sdl1.2/surface.cpp \
	src/sdl1.2/types.cpp \
	src/sdl1.2/window.cpp

libjacui_la_LDFLAGS = -version-info $(JACUI_SO_VERSION)

libjacui_includedir = $(includedir)/jacui

libjacui_include_HEADERS = \
	src/jacui/canvas.hpp \
	src/jacui/cursor.hpp \
	src/jacui/cursors.hpp \
	src/jacui/error.hpp \
	src/jacui/event.hpp \
	src/jacui/font.hpp \
	src/jacui/image.hpp \
	src/jacui/surface.hpp \
	src/jacui/types.hpp \
	src/jacui/window.hpp
