AUTOMAKE_OPTIONS	= foreign

CFLAGS			= -I$(top_srcdir)/sv_util -I$(top_srcdir)/sv_parser -I$(top_srcdir)/sv_interface -I$(top_srcdir)/sv_rsamd5 -I$(top_srcdir)/sv_include -g

noinst_LTLIBRARIES      = libinterface.la
libinterface_la_SOURCES = interp.c  message.c  message2.c  script.c  script2.c  tree.c
libinterface_la_LDFLAGS = -no-undefined -version-info 0:0:0
