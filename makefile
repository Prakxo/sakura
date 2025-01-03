NAME := VN
OUTPUT := $(NAME).elf
BUILD_DIR := build/
TARGET_PC ?= 1
NO64BIT ?= 1

DEBUG ?= 0

BINUTILS_PREFIX := 
CC := $(BINUTILS_PREFIX)gcc
LD := $(BINUTILS_PREFIX)ld
AR := $(BINUTILS_PREFIX)gcc-ar


VNLIB := vnlib
SRC_DIRS := $(shell find example/src -type d)

VNLIB_FILES := $(foreach dir,$(VNLIB),$(wildcard $(dir)/*.c))

ifeq ($(TARGET_PC), 1)
VNLIB_FILES += $(foreach dir,$(VNLIB)/pc,$(wildcard $(dir)/*.c))
endif


C_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

C_FILES += $(VNLIB_FILES)

O_FILES := $(C_FILES:.c=.o)

MINIAUDIO_FLAGS :=
LZ4_FLAGS := 
STB_IMAGE_FLAGS :=


INCLUDE_CFLAGS = -I . -I example/include -I $(VNLIB)

CFLAGS:= -std=c99
LIBS :=

ifeq ($(NO64BIT), 1)
CFLAGS += -m32
MINIAUDIO_FLAGS += $(CFLAGS)
LZ4_FLAGS += $(CFLAGS)
STB_IMAGE_FLAGS += $(CFLAGS)
endif

ifeq ($(DEBUG),1)
CFLAGS += -DDEBUG -g #-fsanitize=address
MINIAUDIO_FLAGS += $(CFLAGS)
LZ4_FLAGS += $(CFLAGS)
STB_IMAGE_FLAGS += $(CFLAGS)
LIBS += -Llib -l:miniaudio.a  -Llib -l:lz4.a -lm -ldl -lpthread -l:stb_image.a -lSDL2 -lm -lasound -lm -ldl -lpthread -lpulse-simple -pthread \
-lpulse -pthread -lX11 -lXext -lXcursor -lXinerama -lXi -lXfixes -lXrandr -lXss -lXxf86vm -ldrm -lgbm -lwayland-egl -lwayland-client \
-lwayland-cursor -lxkbcommon -ldecor-0 -lpthread -lrt
else
CFLAGS += -O
LZ4_FLAGS += -O3
STB_IMAGE_FLAGS += -O3
LIBS += -Llib -l:miniaudio.a  -Llib -l:lz4.a -lm -ldl -lpthread -l:stb_image.a -lSDL2
endif

ifeq ($(TARGET_PC), 1)
CFLAGS += -DTARGET_PC -D_XOPEN_SOURCE=600 -I/usr/include/SDL2 -D_REENTRANT
endif


CFLAGS += $(INCLUDE_CFLAGS)

LDFLAGS := -Map $(NAME).map


#default:
#	$(CC) -c $(CFLAGS) $(C_FILES) -Llib -l:miniaudio.a -lm -ldl -lpthread
#	$(LD) $(LDFLAGS) -o $(OUTPUT) $(BUILD_DIR)$(O_FILES) 


default:
	$(CC) $(CFLAGS) $(C_FILES) -o $(OUTPUT) $(LIBS)

dirs:
	mkdir -p

libs:
	$(CC) $(MINIAUDIO_FLAGS) -c lib/miniaudio.c -o lib/miniaudio.o
	$(AR) cr lib/miniaudio.a ./lib/miniaudio.o
	$(CC) $(LZ4_FLAGS) -c lib/lz4.c -o lib/lz4.o
	$(AR) cr lib/lz4.a ./lib/lz4.o
	$(CC) $(STB_IMAGE_FLAGS) -c lib/stb_image.c -o lib/stb_image.o
	$(AR) cr lib/stb_image.a ./lib/stb_image.o
	
strip:
	$(shell strip $(OUTPUT)) 

clean:
	$(RM) $(OUTPUT)
	
