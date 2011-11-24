ACLOCAL_AMFLAGS         = -I m4
AUTOMAKE_OPTIONS        = foreign

EXTRA_DIST              = libsieve.pc.in src/sv_regex/README src/sv_regex/regcomp.c src/sv_regex/regexec.c src/sv_regex/regex_internal.c src/sv_regex/regex_internal.h
pkgconfigdir            = $(libdir)/pkgconfig
pkgconfig_DATA          = libsieve.pc

SUBDIRS                 = . src/sv_test
include_HEADERS		= src/sv_include/sieve2.h src/sv_include/sieve2_error.h

AM_CFLAGS		= -Wall -I$(top_srcdir)/src/sv_util -I$(top_srcdir)/src/sv_parser -I$(top_srcdir)/src/sv_interface -I$(top_srcdir)/src/sv_regex -I$(top_srcdir)/src/sv_include -g
AM_LFLAGS		= -s -olex.yy.c
AM_YFLAGS		= -d -p$*

noinst_LTLIBRARIES      = src/sv_parser/libparser.la src/sv_regex/libregex.la src/sv_interface/libinterface.la src/sv_util/libutil.la

src_sv_parser_libparser_la_SOURCES    = src/sv_parser/addr.y src/sv_parser/addr-lex.l src/sv_parser/sieve.y src/sv_parser/sieve-lex.l src/sv_parser/header.y src/sv_parser/header-lex.l src/sv_parser/comparator.c
src_sv_parser_libparser_la_LDFLAGS    = -no-undefined

src_sv_regex_libregex_la_SOURCES     = src/sv_regex/regex.h src/sv_regex/regex.c
src_sv_regex_libregex_la_LDFLAGS     = -no-undefined

src_sv_interface_libinterface_la_SOURCES = src/sv_interface/tree.c  src/sv_interface/message.c src/sv_interface/script.c src/sv_interface/message2.c src/sv_interface/script2.c src/sv_interface/context2.c src/sv_interface/callbacks2.c
src_sv_interface_libinterface_la_LDFLAGS = -no-undefined

src_sv_util_libutil_la_SOURCES      = src/sv_util/util.c src/sv_util/md5.c src/sv_util/exception.c
src_sv_util_libutil_la_LDFLAGS      = -no-undefined

lib_LTLIBRARIES         = src/libsieve.la
src_libsieve_la_SOURCES     = src/sv_empty.c
src_libsieve_la_LDFLAGS     = -no-undefined -version-info 1:5
src_libsieve_la_LIBADD      = src/sv_util/libutil.la src/sv_parser/libparser.la src/sv_interface/libinterface.la src/sv_regex/libregex.la
