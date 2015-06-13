SPARROW_FOLDER = ../sparrow3d

#==stuff linked to
STATIC = -Wl,-rpath=$(SPARROW_FOLDER) -Wl,-Bstatic -lsparrow3d -Wl,-Bdynamic
DYNAMIC = -lSDL_ttf -lSDL_mixer -lSDL_image -lSDL -lm
#==global Flags. Even on the gp2x with 16 kb Cache, -O3 is much better then -Os
CFLAGS = -fsingle-precision-constant -fPIC
# Testtweaks: -fgcse-lm -fgcse-sm -fsched-spec-load -fmodulo-sched -funsafe-loop-optimizations -Wunsafe-loop-optimizations -fgcse-las -fgcse-after-reload -fvariable-expansion-in-unroller -ftracer -fbranch-target-load-optimize
GENERAL_TWEAKS = -ffast-math
#==PC==
FLAGS = -g -DDESKTOP $(GENERAL_TWEAKS)
SDL = `sdl-config --cflags`

ifdef TARGET
include $(SPARROW_FOLDER)/target-files/$(TARGET).mk
BUILD = ./build/$(TARGET)/hase_sprite_tester
SPARROW_LIB = $(SPARROW_FOLDER)/build/$(TARGET)/sparrow3d
ifeq ($(TARGET),win32)
	#the BUILDING_DLL is important for the linking...
	STATIC = $(SPARROW_LIB)/libsparrow3d_static.a
endif
else
TARGET = "Default (change with make TARGET=otherTarget. See All targets with make targets)"
BUILD = .
SPARROW_LIB = $(SPARROW_FOLDER)
endif
LIB += -L$(SPARROW_LIB)
INCLUDE += -I$(SPARROW_FOLDER)

CFLAGS += $(FLAGS) $(PARAMETER) -DBUILDING_DLL

all: hase_sprite_tester
	@echo "=== Built for Target "$(TARGET)" ==="

targets:
	@echo "The targets are the same like for sparrow3d. :P"

hase_sprite_tester: hase_sprite_tester.c makeBuildDir
	$(CC) $(CFLAGS) $(LINK_FLAGS) hase_sprite_tester.c $(SDL) $(INCLUDE) $(LIB) $(STATIC) $(DYNAMIC) -o $(BUILD)/hase_sprite_tester$(SUFFIX)

makeBuildDir:
	 @if [ ! -d $(BUILD:/hase_sprite_tester=/) ]; then mkdir $(BUILD:/hase_sprite_tester=/);fi
	 @if [ ! -d $(BUILD) ]; then mkdir $(BUILD);fi

clean:
	rm -f *.o
	rm -f hase_sprite_tester

oclean:
	rm -f *.o
