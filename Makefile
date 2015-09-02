#========================================================================
# FILE:
#   Makefile
#
# AUTHOR:
#   zimzum@github 
#
# DESCRIPTION:
#   This is a very basic Makefile. Everything is hardcoded. Call:
#
#   ~/cdecl$ make cdecl
#
#   to generate an executable called 'cdecl'.
#
# License: GNU GPL v2.0 
#========================================================================
CXX = clang-3.4
COMPILE.cpp = $(CXX) -Weverything

cdecl: cdecl.o
	$(CXX) cdecl.o main_cdecl.c -o cdecl

%.o: %.c
	@echo Compiling $<
	$(COMPILE.cpp) -c $<
