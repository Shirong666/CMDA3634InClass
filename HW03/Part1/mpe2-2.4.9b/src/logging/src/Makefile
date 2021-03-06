#  (C) 1993 by Argonne National Laboratory and Mississipi State University.
#      All rights reserved.  See COPYRIGHT in top-level directory.
#

##### User configurable options #####

top_srcdir           = ..

CC                   = cc
CC_SHL               = @CC_SHL@
CLINKER              = cc
MPI_CC               = /usr/bin/mpicc
MPI_CLINKER          = $(MPI_CC)
MPI_CFLAGS           = -I/usr/lib/openmpi/include 
AR                   = ar
ARFLAGS              = cr
RANLIB               = ranlib
MAKE                 = make --no-print-directory
MPI_LIBS             = -L/usr/lib/openmpi/mpi -lmpi
INCLUDE_DIR          = -I.. -I../../.. \
                       -I../include -I${top_srcdir}/include \
                       -I${includebuild_dir} -I${top_srcdir}/../../include
PROF_LIBNAME         = mpe
CFLAGS               = 
MPE_LIBDIR           = /home/shirong/CMDA3634InClass/HW03/Part1/mpe2-2.4.9b/lib
LIB_PATH             = $(MPI_LIBS)
PROF_LIBS            = -L$(MPE_LIBDIR) @PROF_LIBS@ $(MPI_LIBS)
LDFLAGS              = 
MPE_BUILD_FORTRAN2C  = no
CC_DOES_C_O          = yes

### End User configurable options ###

SHELL            = /bin/bash
RM               = rm
MV               = mv
CP               = cp

VPATH=.:$(srcdir)

# Installation directories
prefix           = /usr/local
exec_prefix      = ${prefix}
bindir           = ${exec_prefix}/bin
includedir       = ${prefix}/include
libdir           = ${exec_prefix}/lib
# Build directories
includebuild_dir = /home/shirong/CMDA3634InClass/HW03/Part1/mpe2-2.4.9b/include
libbuild_dir     = /home/shirong/CMDA3634InClass/HW03/Part1/mpe2-2.4.9b/lib
binbuild_dir     = /home/shirong/CMDA3634InClass/HW03/Part1/mpe2-2.4.9b/bin
srcdir           = .

EXECS            = ${binbuild_dir}/clog2_print \
                   ${binbuild_dir}/clog2_join \
                   ${binbuild_dir}/clog2_repair

# GETNAME_DEFS are needed by mpehname.c
CC_FLAGS         = $(INCLUDE_DIR) $(CFLAGS) $(MPE_COPTS)
CC_LDFLAGS       = $(LDFLAGS) $(CFLAGS) $(MPE_LDOPTS)
# MPE include path, x_INCS, goes in front of MPI include path, MPI_xFLAGS,
# in case MPI include path is in MPI_xFLAGS containing old MPE include path.
MPICC_FLAGS      = $(INCLUDE_DIR) $(MPI_CFLAGS) $(MPE_COPTS)
MPICC_LDFLAGS    = $(LDFLAGS) $(MPI_CFLAGS) $(MPE_LDOPTS)

MPE_ZSOURCES     = mpi_null.c
MPE_N_ZOBJECTS   = $(MPE_ZSOURCES:.c=.no)

MPE_CSOURCES     = clog_util.c clog_timer.c clog_uuid.c clog_commset.c \
                   clog_preamble.c clog_record.c clog_sync.c \
                   clog_block.c clog_buffer.c clog_merger.c \
                   clog_cache.c clog_joiner.c clog.c \
                   mpe_log_thread.c mpe_log.c
MPE_P_COBJECTS   = $(MPE_CSOURCES:.c=.po)
MPE_N_COBJECTS   = $(MPE_CSOURCES:.c=.no)

MPE_WSOURCES     = mpe_logf.c
MPE_P_WOBJECTS   = $(MPE_WSOURCES:.c=.po)
MPE_N_WOBJECTS   = $(MPE_WSOURCES:.c=.no)

MPE_XSOURCES     = mpe_log_null.c
MPE_P_XOBJECTS   = $(MPE_XSOURCES:.c=.po)
MPE_N_XOBJECTS   = $(MPE_XSOURCES:.c=.no)

MPE_SHLCOBJECTS  = $(MPE_COBJECTS:.o=.lo)
MPE_SHLWOBJECTS  = $(MPE_WOBJECTS:.o=.lo)

.SUFFIXES: .c .o .po .no .lo .a 

.c.po:
	@if [ "$(CC_DOES_C_O)" = "yes" ]; then \
	     cmd="$(MPI_CC) $(MPICC_FLAGS) -o $@ -c $<" ; \
	 else \
	     cmd="$(MPI_CC) $(MPICC_FLAGS) -c $< ; $(MV) $*.o $*.po" ; \
	 fi ; \
	 echo "$${cmd}" ; $${cmd}

.c.no:
	@if [ "$(CC_DOES_C_O)" = "yes" ]; then \
	     cmd="$(CC) $(CC_FLAGS) -DCLOG_NOMPI -o $@ -c $<" ; \
	 else \
	     cmd="$(CC) $(CC_FLAGS) -DCLOG_NOMPI -c $< ; $(MV) $*.o $*.no" ; \
	 fi ; \
	 echo "$${cmd}" ; $${cmd}

# Allow compilers that do not allow -o for renaming object files
.c.lo:
	$(CC_SHL) $(CC_FLAGS) -c $< $(INC_DIR)
	@$(MV) $*.o $*.lo

# default_all is the same as default, but without the RANLIB.  This
# can speed up the build (ranlibs can take a LONG time).  profile_all 
# is the same, but for the profile library
# **** Currently the same as default for simplicity ****
default_all: default
profile_all: 

#
default: $(MPE_N_ZOBJECTS) $(MPE_N_COBJECTS) $(MPE_N_ZOBJECTS) $(MPE_N_XOBJECTS) $(MPE_P_XOBJECTS) $(MPE_P_COBJECTS)
	$(MAKE) $(MAKEOPTS) ${libbuild_dir}/lib$(PROF_LIBNAME)_nompi.a
	$(MAKE) $(MAKEOPTS) ${libbuild_dir}/lib$(PROF_LIBNAME)_nompi_null.a
	$(MAKE) $(MAKEOPTS) ${libbuild_dir}/lib$(PROF_LIBNAME)_null.a
	$(MAKE) $(MAKEOPTS) ${libbuild_dir}/lib$(PROF_LIBNAME).a
	$(MAKE) $(MAKEOPTS) $(EXECS)

#
# It is tempting here to use ... libmpe.a($(MPE_OBJECTS)) as the dependency,
# but this would require that all makes properly handle library dependencies.
# Since makes that DO are the exception rather than the rule, we don't
# use this form
#
# We've also had trouble with this.  Sometimes, under Solaris, the 
# first file in the dependency is built but not included with $? 
# This is clearly a bug in the make, since the determination of dependencies
# is done once (e.g., a blip in the filesystem time can't be 
# responsible if make works as Sun documents it).  To fix this, we
# add all the objects to the library, not just the "recent" ones.
${libbuild_dir}/lib$(PROF_LIBNAME).a: $(MPE_P_COBJECTS)
	$(AR) $(ARFLAGS) $@ $(MPE_P_COBJECTS)
	@if [ "$(MPE_BUILD_FORTRAN2C)" = "yes" ] ; then \
	     $(MAKE) $(MAKEOPTS) $(MPE_P_WOBJECTS) ; \
	     $(AR) $(ARFLAGS) $@ $(MPE_P_WOBJECTS) ; \
	 fi
	$(RANLIB) $@

${libbuild_dir}/lib$(PROF_LIBNAME)_nompi.a: $(MPE_N_ZOBJECTS) $(MPE_N_COBJECTS)
	$(AR) $(ARFLAGS) $@ $(MPE_N_ZOBJECTS) $(MPE_N_COBJECTS)
	@if [ "$(MPE_BUILD_FORTRAN2C)" = "yes" ] ; then \
	     $(MAKE) $(MAKEOPTS) $(MPE_N_WOBJECTS) ; \
	     $(AR) $(ARFLAGS) $@ $(MPE_N_WOBJECTS) ; \
	 fi
	$(RANLIB) $@

# -DCLOG_NOMPI can be used when creating lib$(PROF_LIBNAME)_null.a
${libbuild_dir}/lib$(PROF_LIBNAME)_null.a: $(MPE_P_XOBJECTS)
	$(AR) $(ARFLAGS) $@ $(MPE_P_XOBJECTS)
	@if [ "$(MPE_BUILD_FORTRAN2C)" = "yes" ] ; then \
	     $(MAKE) $(MAKEOPTS) $(MPE_P_WOBJECTS) ; \
	     $(AR) $(ARFLAGS) $@ $(MPE_P_WOBJECTS) ; \
	 fi
	$(RANLIB) $@

# -DCLOG_NOMPI can be used when creating lib$(PROF_LIBNAME)_nompi_null.a
${libbuild_dir}/lib$(PROF_LIBNAME)_nompi_null.a: $(MPE_N_ZOBJECTS) $(MPE_N_XOBJECTS)
	$(AR) $(ARFLAGS) $@ $(MPE_N_ZOBJECTS) $(MPE_N_XOBJECTS)
	@if [ "$(MPE_BUILD_FORTRAN2C)" = "yes" ] ; then \
	     $(MAKE) $(MAKEOPTS) $(MPE_N_WOBJECTS) ; \
	     $(AR) $(ARFLAGS) $@ $(MPE_N_WOBJECTS) ; \
	 fi
	$(RANLIB) $@

# Link with *.o instead of *.no
# as NEC SX-8's cross-compiler refuses to link with *.no
${binbuild_dir}/clog2_print: clog_print.no
	$(CP) -f clog_print.no mpe2tmp1.o
	$(CLINKER) $(CC_LDFLAGS) -o $@ mpe2tmp1.o \
	                         -L${libbuild_dir} -l$(PROF_LIBNAME)_nompi
	@-$(RM) -f mpe2tmp1.o

${binbuild_dir}/clog2_join: clog_join.no
	$(CP) -f clog_join.no mpe2tmp2.o
	$(CLINKER) $(CC_LDFLAGS) -o $@ mpe2tmp2.o \
	                         -L${libbuild_dir} -l$(PROF_LIBNAME)_nompi
	@-$(RM) -f mpe2tmp2.o

${binbuild_dir}/clog2_repair: clog_repair.no
	$(CP) -f clog_repair.no mpe2tmp3.o
	$(CLINKER) $(CC_LDFLAGS) -o $@ mpe2tmp3.o \
	                         -L${libbuild_dir} -l$(PROF_LIBNAME)_nompi
	@-$(RM) -f mpe2tmp3.o

#
# Remove the old libraries before rebuilding (in case they came from another
# architecture or are otherwise damaged)
rmlib:
	@-$(RM) -f ${libbuild_dir}/lib$(PROF_LIBNAME).a 
	@-$(RM) -f ${libbuild_dir}/lib$(PROF_LIBNAME)_null.a
	@-$(RM) -f ${libbuild_dir}/lib$(PROF_LIBNAME)_nompi_null.a
	@-$(RM) -f ${libbuild_dir}/lib$(PROF_LIBNAME)_nompi.a 

rmprog:
	@-$(RM) -f $(EXECS)

clean: rmprog
	@-$(RM) -f ${srcdir}/*.*o *.*o *~ PI*

distclean: clean rmlib
	@-$(RM) -f Makefile
