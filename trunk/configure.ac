AC_INIT([jacui], [0.2.1], [perlkoenig@gmail.com], [jacui], [http://code.google.com/p/jacui/])
AC_PREREQ([2.59])

AM_INIT_AUTOMAKE([1.10 -Wall no-define])
AC_PROG_CXX
LT_INIT

AC_SUBST([SO_VERSION], [1:0:1])

AC_ARG_WITH([sdl-include-path],
        [AS_HELP_STRING([--with-sdl-include-path], 
        [location of the SDL headers, defaults to /usr/include/SDL])],
        [SDL_CFLAGS="-I$withval"],
        [SDL_CFLAGS="-I/usr/include/SDL"])
AC_SUBST([SDL_CFLAGS])

AC_ARG_WITH([sdl-lib-path],
        [AS_HELP_STRING([--with-sdl-lib-path], 
        [location of the SDL libraries])],
        [SDL_LIBS="-L$withval  -lSDL_ttf -lSDL_image -lSDL"],
        [SDL_LIBS="-lSDL_ttf -lSDL_image -lSDL"])
AC_SUBST([SDL_LIBS])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
