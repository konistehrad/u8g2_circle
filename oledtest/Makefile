#
# Makefile
#

CIRCLEHOME = ../..

OBJS	= main.o kernel.o

LIBS	= $(CIRCLEHOME)/app/lib/u8g2/libu8g2.a \
	  	  $(CIRCLEHOME)/lib/libcircle.a \
		  $(CIRCLEHOME)/lib/input/libinput.a \
		  $(CIRCLEHOME)/lib/sched/libsched.a \
		  $(CIRCLEHOME)/lib/usb/libusb.a \
		  $(CIRCLEHOME)/lib/fs/libfs.a \
		  $(CIRCLEHOME)/lib/fs/fat/libfatfs.a

include ../Rules.mk
