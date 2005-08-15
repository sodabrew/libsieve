AUTOMAKE_OPTIONS	= foreign

if ENABLE_DEBUG
DEBUG			= -DDEBUG
endif

CFLAGS			= -Wall -I$(top_srcdir)/sv_util -I$(top_srcdir)/sv_parser -I$(top_srcdir)/sv_interface -I$(top_srcdir)/sv_include -g $(DEBUG)

if ENABLE_TEST
bin_PROGRAMS		= example testcomp
example_LDADD      	= ../libsieve.la
testcomp_LDADD      	= ../libsieve.la
endif
