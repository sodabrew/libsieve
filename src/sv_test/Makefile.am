AUTOMAKE_OPTIONS	= foreign

CFLAGS			= -Wall -I$(top_srcdir)/sv_util -I$(top_srcdir)/sv_parser -I$(top_srcdir)/sv_interface -I$(top_srcdir)/sv_rsamd5 -I$(top_srcdir)/sv_include -g

bin_PROGRAMS            = test test2 testbuf
test_SOURCES    	= test.c
test_LDADD      	= ../libsieve.la
test2_SOURCES    	= test2.c
test2_LDADD      	= ../libsieve.la
testbuf_SOURCES    	= testbuf.c
testbuf_LDADD      	= ../libsieve.la
