AUTOMAKE_OPTIONS	= foreign

SUBDIRS			= sv_parser sv_regex sv_interface sv_util . sv_test sv_include

CFLAGS			= @CFLAGS@ -Wall -I$(top_srcdir)/sv_util -I$(top_srcdir)/sv_parser -I$(top_srcdir)/sv_interface -I$(top_srcdir)/sv_regex -I$(top_srcdir)/sv_include -g

lib_LTLIBRARIES         = libsieve.la
libsieve_la_SOURCES     = sv_empty.c
libsieve_la_LDFLAGS     = -no-undefined -version-info 1:5
libsieve_la_LIBADD      = sv_util/libutil.la  sv_parser/libparser.la  sv_interface/libinterface.la  sv_regex/libregex.la
