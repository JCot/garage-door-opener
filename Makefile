#
# Created by gmakemake (Ubuntu Sep  7 2011) on Sun Mar 16 14:56:24 2014
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Default flags (redefine these with a header.mak file if desired)
CXXFLAGS =	-ggdb
CFLAGS =	-ggdb
CLIBFLAGS =	-lm
CCLIBFLAGS = -pthread
########## End of default flags


CPP_FILES =	Controller.cpp Input.cpp Motor.cpp global.cpp
C_FILES =	
PS_FILES =	
S_FILES =	
H_FILES =	Controller.h Input.h Motor.h global.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	Input.o Motor.o global.o 

#
# Main targets
#

all:	Controller 

Controller:	Controller.o $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o garage-door-opener Controller.o $(OBJFILES) $(CCLIBFLAGS)

#
# Dependencies
#

Controller.o:	Controller.h Input.h Motor.h global.h
Input.o:	Input.h global.h
Motor.o:	Motor.h global.h
global.o:	global.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm $(OBJFILES) Controller.o core 2> /dev/null

realclean:        clean
	-/bin/rm -rf garage-door-opener 
