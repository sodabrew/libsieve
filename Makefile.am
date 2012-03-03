ACLOCAL_AMFLAGS         = -I m4
AUTOMAKE_OPTIONS        = foreign

EXTRA_DIST              = libsieve.pc.in src/sv_regex/README src/sv_regex/regcomp.c src/sv_regex/regexec.c src/sv_regex/regex_internal.c src/sv_regex/regex_internal.h src/sv_test/lmtp-1 src/sv_test/lmtp-2 src/sv_test/messagea.mbox src/sv_test/messageb.mbox src/sv_test/messagec.mbox src/sv_test/messaged.mbox src/sv_test/messagef.mbox src/sv_test/messageg.mbox src/sv_test/messageh.mbox src/sv_test/messagei.mbox src/sv_test/messagej.mbox src/sv_test/messagek.mbox src/sv_test/script10.sv src/sv_test/script11.sv src/sv_test/script12.sv src/sv_test/script13.sv src/sv_test/script14.sv src/sv_test/script15.sv src/sv_test/script16.sv src/sv_test/script17.sv src/sv_test/script18.sv src/sv_test/script19.sv src/sv_test/script1.sv src/sv_test/script20.sv src/sv_test/script21.sv src/sv_test/script22.sv src/sv_test/script23.sv src/sv_test/script2.sv src/sv_test/script3.sv src/sv_test/script4.sv src/sv_test/script5.sv src/sv_test/script6.sv src/sv_test/script7.sv src/sv_test/script8.sv src/sv_test/script9.sv src/sv_test/testmessage.sh src/sv_test/testvalid.sh
pkgconfigdir            = $(libdir)/pkgconfig
pkgconfig_DATA          = libsieve.pc

include_HEADERS		= src/sv_include/sieve2.h src/sv_include/sieve2_error.h

AM_CFLAGS		= -Wall -I$(top_srcdir) -I$(top_srcdir)/src/sv_include -I$(top_builddir) ${CFLAG_VISIBILITY}
AM_LFLAGS		= -s -olex.yy.c
AM_YFLAGS		= -d -p$*

noinst_LTLIBRARIES      = src/sv_parser/libparser.la src/sv_regex/libregex.la src/sv_interface/libinterface.la src/sv_util/libutil.la

noinst_PROGRAMS		= src/sv_test/example src/sv_test/testcomp
src_sv_test_example_LDADD      	= src/libsieve.la
src_sv_test_testcomp_LDADD     	= src/libsieve.la

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
