AUTOMAKE_OPTIONS	= foreign

AM_CFLAGS			= -Wall -I$(top_srcdir)/src/sv_util -I$(top_srcdir)/src/sv_parser -I$(top_srcdir)/src/sv_interface -I$(top_srcdir)/src/sv_regex -I$(top_srcdir)/src/sv_include -g

noinst_LTLIBRARIES      = libregex.la
libregex_la_SOURCES     = regex.c
libregex_la_LDFLAGS     = -no-undefined
