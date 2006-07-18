AUTOMAKE_OPTIONS	= foreign

if ENABLE_DEBUG
DEBUG			= -DDEBUG
endif

CFLAGS			= -Wall -I$(top_srcdir)/sv_util -I$(top_srcdir)/sv_parser -I$(top_srcdir)/sv_interface -I$(top_srcdir)/sv_include -g $(DEBUG)

noinst_LTLIBRARIES      = libutil.la
libutil_la_SOURCES      = util.c md5.c vasprintf.c vasnprintf.c printf-parse.c printf-args.c
libutil_la_LDFLAGS      = -no-undefined
