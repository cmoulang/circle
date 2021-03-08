#
# Makefile
#

CIRCLEHOME = ../..

OBJS	=  joystick.o wildcard.o atmmc2wfn.o atmmc2core.o gpioutils.o clogobj.o multicore.o main.o kernel.o pl8if.o utils.o

LIBS	= $(CIRCLEHOME)/addon/fatfs/libfatfs.a \
	  $(CIRCLEHOME)/addon/SDCard/libsdcard.a \
	  $(CIRCLEHOME)/lib/usb/libusb.a \
	  $(CIRCLEHOME)/lib/input/libinput.a \
	  $(CIRCLEHOME)/lib/fs/libfs.a \
	  $(CIRCLEHOME)/lib/libcircle.a

include ../Rules.mk

all:	$(TARGET).img

-include $(DEPS)

$(info INCLUDE is $(INCLUDE))

