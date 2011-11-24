ACLOCAL_AMFLAGS         = -I m4
AUTOMAKE_OPTIONS        = foreign

EXTRA_DIST              = libsieve.pc.in
pkgconfigdir            = $(libdir)/pkgconfig
pkgconfig_DATA          = libsieve.pc

SUBDIRS                 = src/sv_parser src/sv_regex src/sv_interface src/sv_util . src/sv_test src/sv_include

AM_CFLAGS                  = -Wall -I$(top_srcdir)/src/sv_util -I$(top_srcdir)/src/sv_parser -I$(top_srcdir)/src/sv_interface -I$(top_srcdir)/src/sv_regex -I$(top_srcdir)/src/sv_include -g

lib_LTLIBRARIES         = src/libsieve.la
src_libsieve_la_SOURCES     = src/sv_empty.c
src_libsieve_la_LDFLAGS     = -no-undefined -version-info 1:5
src_libsieve_la_LIBADD      = src/sv_util/libutil.la src/sv_parser/libparser.la src/sv_interface/libinterface.la src/sv_regex/libregex.la
