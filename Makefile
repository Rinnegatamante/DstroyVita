TARGET		:= DstroyVita
TITLE		:= DSTROYVIT
SOURCES		:= src
			
INCLUDES	:= include

PKG_CONFIG = arm-vita-eabi-pkg-config
SDL_LIBS := $(shell $(PKG_CONFIG) --static --libs SDL_image SDL_mixer)

LIBS = $(SDL_LIBS) -lSDL_image -lSDL_mixer -lSceAudio_stub -lSceLibKernel_stub -lSceDisplay_stub -lSceGxm_stub	\
	-lSceSysmodule_stub -lSceCtrl_stub -lSceTouch_stub -lm -lSceNet_stub -lvorbis -limgui -lmathneon \
	-lSceNetCtl_stub -lScePgf_stub -ljpeg -lfreetype -lc -lSDL -limgui -lvitaGL -lSceHid_stub \
	-lScePower_stub -lSceCommonDialog_stub -lpng16 -lz -lSceAppMgr_stub -logg -lvorbisfile -lmikmod \
	-lvitashark -lSceShaccCgExt -ltaihen_stub -lSceShaccCg_stub -lSceKernelDmacMgr_stub -lSceAppUtil_stub

CFILES   := $(foreach dir,$(SOURCES), $(wildcard $(dir)/*.c))
CPPFILES   := $(foreach dir,$(SOURCES), $(wildcard $(dir)/*.cpp))
BINFILES := $(foreach dir,$(DATA), $(wildcard $(dir)/*.bin))
OBJS     := $(addsuffix .o,$(BINFILES)) $(CFILES:.c=.o) $(CPPFILES:.cpp=.o) 

PREFIX  = arm-vita-eabi
CC      = $(PREFIX)-gcc
CXX      = $(PREFIX)-g++
CFLAGS  = -g -Wl,-q -O2 -ftree-vectorize -I$(VITASDK)/$(PREFIX)/include/SDL -flto
CXXFLAGS  = $(CFLAGS) -fno-exceptions -std=gnu++11 -fpermissive -DTGI_NONET
ASFLAGS = $(CFLAGS)

all: $(TARGET).vpk

$(TARGET).vpk: $(TARGET).velf
	vita-make-fself -s $< build/eboot.bin
	vita-mksfoex -s TITLE_ID=$(TITLE) -d ATTRIBUTE2=12 "$(TARGET)" param.sfo
	cp -f param.sfo build/sce_sys/param.sfo
	vita-pack-vpk -s param.sfo -b build/eboot.bin \
		--add build/sce_sys/icon0.png=sce_sys/icon0.png \
		--add build/sce_sys/pic0.png=sce_sys/pic0.png \
		--add build/sce_sys/livearea=sce_sys/livearea \
		--add build/shaders=shaders $@

%.velf: %.elf
	cp $< $<.unstripped.elf
	$(PREFIX)-strip -g $<
	vita-elf-create $< $@
	vita-make-fself -s $@ eboot.bin

$(TARGET).elf: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

clean:
	@rm -rf $(TARGET).velf $(TARGET).elf $(OBJS)
