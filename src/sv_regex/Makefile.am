AUTOMAKE_OPTIONS	= foreign

CFLAGS			= @CFLAGS@ -Wall -I$(top_srcdir)/sv_util -I$(top_srcdir)/sv_parser -I$(top_srcdir)/sv_interface -I$(top_srcdir)/sv_regex -I$(top_srcdir)/sv_include -g

noinst_LTLIBRARIES      = libregex.la
libregex_la_SOURCES     = regex.c
libregex_la_LDFLAGS     = -no-undefined
