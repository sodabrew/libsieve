AUTOMAKE_OPTIONS	= foreign

CFLAGS			= @CFLAGS@ -Wall -I$(top_srcdir)/sv_util -I$(top_srcdir)/sv_parser -I$(top_srcdir)/sv_interface -I$(top_srcdir)/sv_include -g

noinst_LTLIBRARIES      = libutil.la
libutil_la_SOURCES      = util.c md5.c exception.c
libutil_la_LDFLAGS      = -no-undefined
