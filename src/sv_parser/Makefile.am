AUTOMAKE_OPTIONS	= foreign

CFLAGS			= @CFLAGS@ -Wall -I$(top_srcdir)/sv_util -I$(top_srcdir)/sv_parser -I$(top_srcdir)/sv_interface -I$(top_srcdir)/sv_regex -I$(top_srcdir)/sv_include -g
LFLAGS			= -s -olex.yy.c
YFLAGS			= -d -p$*

noinst_LTLIBRARIES      = libparser.la
libparser_la_SOURCES    = addr.y  addr-lex.l  sieve.y  sieve-lex.l  sieve-keywords.c  sieve-encodedchar.c  header.y  header-lex.l  comparator.c
libparser_la_LDFLAGS    = -no-undefined

# Handling the Gperf code
BUILT_SOURCES = sieve-keywords.c

sieve-keywords.c: sieve-keywords.gperf
	if $(GPERF) $(GPERFFLAGS) $< >$@t; then \
	  mv $@t $@; \
	elif $(GPERF) --version >/dev/null 2>&1; then \
	  rm $@t; \
	  exit 1; \
	else \
	  rm $@t; \
	  touch $@; \
	fi

