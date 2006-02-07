AUTOMAKE_OPTIONS	= foreign

if ENABLE_DEBUG
DEBUG			= -DDEBUG
endif

if ENABLE_REGEX
REGEX			= -DENABLE_REGEX
endif

CFLAGS			= -Wall -I$(top_srcdir)/sv_util -I$(top_srcdir)/sv_parser -I$(top_srcdir)/sv_interface -I$(top_srcdir)/sv_regex -I$(top_srcdir)/sv_include -g $(DEBUG) $(REGEX)
LFLAGS			= -s -olex.yy.c
YFLAGS			= -d -p$*

noinst_LTLIBRARIES      = libparser.la
libparser_la_SOURCES    = addr.y  addr-lex.l  sieve.y  sieve-lex.l  header.y  header-lex.l  comparator.c
libparser_la_LDFLAGS    = -no-undefined

