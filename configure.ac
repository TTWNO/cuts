#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([cuts], [0.0.1a], [44244401+TTWNO@users.noreply.github.com])
AC_CONFIG_SRCDIR([lib/Catch2/include/catch_with_main.hpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_MAKE_SET

# Automake
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])

# Libtool

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lboost_regex':
AC_CHECK_LIB([boost_regex], [main])

# Checks for header files.
AC_CHECK_HEADERS([unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([dup2 memset pow])

AC_CONFIG_FILES([Makefile
		])
AC_OUTPUT
