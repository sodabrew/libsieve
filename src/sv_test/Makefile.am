AUTOMAKE_OPTIONS	= foreign

if DEBUG
DEBUG			= -DDEBUG
endif

CFLAGS			= -Wall -I$(top_srcdir)/sv_util -I$(top_srcdir)/sv_parser -I$(top_srcdir)/sv_interface -I$(top_srcdir)/sv_rsamd5 -I$(top_srcdir)/sv_include -g $(DEBUG)

if TEST
bin_PROGRAMS		= test test2 testbuf
test_LDADD      	= ../libsieve.la
test2_LDADD      	= ../libsieve.la
testbuf_LDADD      	= ../libsieve.la
endif
