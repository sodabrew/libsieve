AUTOMAKE_OPTIONS	= foreign

SUBDIRS			= lib .

CFLAGS			= -I$(top_srcdir)/lib
LFLAGS			= -olex.yy.c
YFLAGS			= -d -p$*

include_HEADERS		= addr.h config.h interp.h md5.h script.h sieve.h tree.h comparator.h hmac-md5.h md5global.h message.h sieve_interface.h


lib_LTLIBRARIES         = libsieve.la
libsieve_la_SOURCES     = addr.y addr-lex.l sieve.y sieve-lex.l comparator.c interp.c md5.c message.c script.c tree.c
libsieve_la_LDFLAGS     = -no-undefined -version-info 0:0:0
libsieve_la_LIBADD      = lib/libcyrus.la

bin_PROGRAMS            = test
test_SOURCES    	= test.c
test_LDADD      	= libsieve.la
