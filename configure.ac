dnl Process this file with autoconf to produce a configure script.
AC_PREREQ([2.68])
AC_INIT(libsieve, 2.2.8)
AC_CONFIG_SRCDIR(src/sv_parser/sieve.y)
AM_INIT_AUTOMAKE([])

dnl Don't rebuild flex/bison output unless I say so.
AM_MAINTAINER_MODE
AC_CONFIG_MACRO_DIR([m4])
dnl Checks for programs.
AC_PROG_CC
AC_PROG_YACC
AC_PROG_INSTALL
AC_PROG_LIBTOOL

AM_PROG_LEX

dnl Gperf for the Sieve lexer
AM_MISSING_PROG([GPERF], [gperf])

dnl AC_ARG_PROGRAM

dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS(fcntl.h malloc.h unistd.h alloca.h)

dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_SIZE_T
AC_C_BIGENDIAN
AC_CHECK_HEADERS(endian.h)

dnl Checks for library functions.
AC_FUNC_MEMCMP
AC_FUNC_VPRINTF

AM_CONFIG_HEADER(config.h)

AC_CONFIG_FILES([libsieve.pc Makefile])
AC_OUTPUT
