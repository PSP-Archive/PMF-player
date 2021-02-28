TARGET = pmfPlayer

OBJS = src/decoder.o src/reader.o src/video.o src/audio.o src/pmfplayer.o src/main.o

BUILD_PRX = 1
PRX_EXPORTS = src/exports.exp

INCDIR = 
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS = -lpspgu libmpeg/libpspmpeg.a -lpspaudiolib -lpspaudio -lpsppower
USE_PSPSDK_LIBC = 1

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build_prx.mak
