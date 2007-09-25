# includefile contains LOCALDIR-definition

include ../conf/$(OSTYPE).mk

LIBNAME=puCtools
LOCALIDIR=$(LOCALDIR)/include/$(LIBNAME)

INCLUDE=-I../include
DEFINES=-DHAVE_ALLOCA_H


LOCALOPTIONS=
include ../conf/targets.mk
