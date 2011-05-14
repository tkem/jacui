# Process this file with automake to produce Makefile.in

# Make sure that when we re-make ./configure, we get the macros we need
# ACLOCAL_AMFLAGS = -I m4

# This is so we can #include <jacui/foo.hpp>
AM_CPPFLAGS = -I$(top_srcdir)/src/

# This is mostly based on configure options
AM_CXXFLAGS =

AUTOMAKE_OPTIONS = subdir-objects

include_HEADERS = \
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

lib_LTLIBRARIES = libjacui-sdl1.2.la

libjacui_sdl1_2_includedir = $(includedir)/jacui

libjacui_sdl1_2_la_SOURCES = \
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

libjacui_sdl1_2_la_LDFLAGS = -version-info $(SO_VERSION)
libjacui_sdl1_2_la_CPPFLAGS = -I$(top_srcdir)/src $(SDL_CFLAGS)
libjacui_sdl1_2_la_LIBADD = $(SDL_LIBS)

noinst_PROGRAMS = imgview fontview

imgview_SOURCES = \
	examples/imgview.cpp \
	examples/bitstream_vera.hpp \
	examples/bitstream_vera.cpp

imgview_LDADD = libjacui-sdl1.2.la $(SDL_LIBS)

fontview_SOURCES = \
	examples/fontview.cpp \
	examples/bitstream_vera.hpp \
	examples/bitstream_vera.cpp

fontview_LDADD = libjacui-sdl1.2.la $(SDL_LIBS)

docs: Doxyfile Doxymain $(libjacui_sdl1_2_include_HEADERS)
	doxygen Doxyfile

maintainer-clean-local:
	rm -rf docs

EXTRA_DIST = Doxyfile Doxymain docs *.sln *.props *.vcxproj \
	examples/*.vcxproj examples/*.vcxproj.user
