AUTOMAKE_OPTIONS	= foreign

SUBDIRS			= sv_parser sv_rsamd5 sv_regex sv_interface sv_util . sv_test sv_include

if ENABLE_DEBUG
DEBUG			= -DDEBUG
endif

CFLAGS			= -Wall -I$(top_srcdir)/sv_util -I$(top_srcdir)/sv_parser -I$(top_srcdir)/sv_interface -I$(top_srcdir)/sv_rsamd5 -I$(top_srcdir)/sv_regex -I$(top_srcdir)/sv_include -g $(DEBUG)

lib_LTLIBRARIES         = libsieve.la
libsieve_la_SOURCES     = sv_empty.c
libsieve_la_LDFLAGS     = -no-undefined -version-info 2:2:0
libsieve_la_LIBADD      = sv_util/libutil.la  sv_parser/libparser.la  sv_interface/libinterface.la  sv_rsamd5/librsamd5.la sv_regex/libregex.la
