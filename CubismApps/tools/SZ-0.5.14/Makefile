##=======================================================================
###############################################
# COPYRIGHT: See COPYRIGHT.txt                #
# 2015 by MCS, Argonne National Laboratory.   #
###############################################
##=======================================================================

##=======================================================================
##   PLEASE SET THESE VARIABLES BEFORE COMPILING
##=======================================================================

SZPATH		= [SZ_INSTALL_PATH]
#example: SZPATH         = /home/sdi/SZ-0.5
#SZPATH		= /home/fti/workspace-java/SZ_Project/SZ-0.5.14
#SZPATH = /home/chatzidp/DRain_membuffer/soft/SZ-0.5.14
SZPATH=  /home/chatzidp/gitlab/CubismZ/CubismApps/tools/SZ-0.5.14
#JAVAHOME	= [JDK_INSTALL_PATH]
#example: JAVAHOME       = /home/sdi/jdk/jdk1.8.0_05
#JAVAHOME	= /home/fti/jdk/jdk1.8.0_05
#JAVAHOME = /usr/lib/jvm/java-1.8.0-openjdk-1.8.0.77-0.b03.el7_2.x86_64
JAVAHOME = /usr/lib/jvm/java-1.8.0

#ARCHITECTURE is set to linux_x64,linux_x86,linux_arm,solaris, or ppc
#ppc means IBM PowerPC (such as IBM BlueGene series)
ARCHITECTURE	= linux_x64

##=======================================================================
##   DIRECTORY TREE
##=======================================================================

LIB 		= lib
OBJ		= obj
SRC		= src
DOC		= doc
INC		= include

##=======================================================================
##   COMPILERS
##=======================================================================

CC 		= gcc
FT		= gfortran

##=======================================================================
##   FLAGS
##=======================================================================

ifeq ($(ARCHITECTURE),linux_x64)
	SZFLAGS	= -fPIC -g -I$(JAVAHOME)/include -I$(JAVAHOME)/include/linux -Iinclude/ -L$(JAVAHOME)/jre/lib/amd64/server -ljvm -c
endif
ifeq ($(ARCHITECTURE),linux_x86)
	SZFLAGS = -fPIC -g -I$(JAVAHOME)/include -I$(JAVAHOME)/include/linux -Iinclude/ -L$(JAVAHOME)/jre/lib/i386/server -ljvm -c
endif
ifeq ($(ARCHITECTURE),linux_arm)
	SZFLAGS = -fPIC -g -I$(JAVAHOME)/include -I$(JAVAHOME)/include/linux -Iinclude/ -L$(JAVAHOME)/jre/lib/aarch64/server -ljvm -c
endif
ifeq ($(ARCHITECTURE),solaris)
	SZFLAGS = -fPIC -g -I$(JAVAHOME)/include -I$(JAVAHOME)/include/linux -Iinclude/ -L$(JAVAHOME)/jre/lib/amd64/server -ljvm -c
endif
ifeq ($(ARCHITECTURE),ppc)
	SZFLAGS	= -fPIC -g -I$(JAVAHOME)/include -I$(JAVAHOME)/include/linux -Iinclude/ -L$(JAVAHOME)/jre/bin/classic -ljvm -c
endif

##=======================================================================
##   TARGETS
##=======================================================================

#NOTE: If you want to generate shared library libsz.so and use it to run "C-version" compressor instead of using static library libsz.a, 
#      then you must remove the last two lines in the OBJS, i.e., 
#                 #$(OBJ)/sz_interface.o $(OBJ)/rw_interface.o\
#                 #$(OBJ)/rwf.o $(OBJ)/szf.o\
#      If you plan to use static library to run the compressor (either C version or Fortran version), don't have to make any changes for OBJS                                          
OBJS		= $(OBJ)/dictionary.o $(OBJ)/iniparser.o \
		  $(OBJ)/conf.o $(OBJ)/sz.o $(OBJ)/rw.o \
		  $(OBJ)/sz_interface.o $(OBJ)/rw_interface.o\
		  $(OBJ)/rwf.o $(OBJ)/szf.o\

SHARED		= libsz.so
STATIC		= libsz.a

all: 		$(SHARED) $(STATIC)

doc:
		doxygen $(DOC)/Doxyfile

$(OBJ)/%.o:	$(SRC)/%.c
		$(CC) $(SZFLAGS) $< -o $@

$(OBJ)/sz_interface.o:
		$(FT) -c $(SRC)/sz_interface.F90 $(SZFLAGS)
		mv sz_interface.o $(OBJ)
		mv sz.mod $(INC)
		
$(OBJ)/rw_interface.o:
		$(FT) -c $(SRC)/rw_interface.F90 $(SZFLAGS)
		mv rw_interface.o $(OBJ)
		mv rw.mod $(INC)

$(SHARED):	$(OBJS)
		$(CC) -shared -o $(LIB)/$(SHARED) $(OBJS) -lc

$(STATIC):	$(OBJS)
		$(AR) -cvq $(LIB)/$(STATIC) $(OBJS)
install:
		if [ ! -d "$(SZPATH)/SZ" ]; then mkdir $(SZPATH)/SZ; fi
		if [ ! -d "$(SZPATH)/SZ/$(LIB)" ]; then mkdir $(SZPATH)/SZ/$(LIB); fi
		if [ ! -d "$(SZPATH)/SZ/$(INC)" ]; then mkdir $(SZPATH)/SZ/$(INC); fi
		rm -f $(SZPATH)/SZ/$(LIB)/* $(SZPATH)/SZ/$(INC)/*
		cp $(INC)/* $(SZPATH)/SZ/$(INC)/
		cp $(LIB)/* $(SZPATH)/SZ/$(LIB)/

uninstall:
		rm -f $(SZPATH)/SZ/$(LIB)/* $(SZPATH)/SZ/$(INC)/*
		if [ -d "$(SZPATH)/SZ/$(LIB)" ]; then rmdir $(SZPATH)/SZ/$(LIB); fi
		if [ -d "$(SZPATH)/SZ/$(INC)" ]; then rmdir $(SZPATH)/SZ/$(INC); fi
		if [ -d "$(SZPATH)/SZ" ]; then rmdir $(SZPATH)/SZ; fi

clean:
		rm -f $(OBJ)/* $(LIB)/libsz* $(INC)/*.mod

.PHONY:		$(SHARED) $(STATIC) doc install uninstall clean


