AUTOMAKE_OPTIONS	= foreign

CFLAGS			= @CFLAGS@ -Wall -I$(top_srcdir)/sv_util -I$(top_srcdir)/sv_parser -I$(top_srcdir)/sv_interface -I$(top_srcdir)/sv_include -g

noinst_PROGRAMS		= example testcomp
example_LDADD      	= ../libsieve.la
testcomp_LDADD      	= ../libsieve.la
