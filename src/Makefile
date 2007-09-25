THELIB=$(LIBDIR)/libpuCtools.a

LIBOBJ=safety.o stringmanip.o timemanip.o puMath.o getopt.o getopt1.o

LIBSRC=$(LIBOBJ:.o=.c)

VPATH=$(LIBDIR)

.SUFFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) -c $< $(INCLUDE)

all: $(THELIB)

depends:
	rm -f $(DEPENDSFILE)
	echo '# Automatically-generated dependencies list:' > $(DEPENDSFILE)
	$(CC) $(CFLAGS) $(INCLUDE) -M $(LIBSRC) >> $(DEPENDSFILE)

$(THELIB): $(LIBOBJ)
	$(AR) $(ARFLAGS) $@ $(LIBOBJ)

include $(DEPENDSFILE)
