AUTOMAKE_OPTIONS	= foreign

AM_CFLAGS			= -Wall -I$(top_srcdir)/src/sv_util -I$(top_srcdir)/src/sv_parser -I$(top_srcdir)/src/sv_interface -I$(top_srcdir)/src/sv_include -g

noinst_LTLIBRARIES      = libinterface.la
libinterface_la_SOURCES = tree.c  message.c script.c message2.c script2.c context2.c callbacks2.c
libinterface_la_LDFLAGS = -no-undefined
