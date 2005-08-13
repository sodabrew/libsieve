AUTOMAKE_OPTIONS	= foreign

if ENABLE_DEBUG
DEBUG			= -DDEBUG
endif

if ENABLE_REGEX
REGEX			= -DENABLE_REGEX
endif

CFLAGS			= -Wall -I$(top_srcdir)/sv_util -I$(top_srcdir)/sv_parser -I$(top_srcdir)/sv_interface -I$(top_srcdir)/sv_rsamd5 -I$(top_srcdir)/sv_include -g $(DEBUG) $(REGEX)

noinst_LTLIBRARIES      = libinterface.la
libinterface_la_SOURCES = tree.c  message.c script.c message2.c script2.c context2.c callbacks2.c
libinterface_la_LDFLAGS = -no-undefined
