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


C_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

C_FILES += $(VNLIB_FILES)

O_FILES := $(C_FILES:.c=.o)

LIBS_FLAGS :=


INCLUDE_CFLAGS = -I . -I example/include -I $(VNLIB)

CFLAGS:= -std=c99

ifeq ($(NO64BIT), 1)
CFLAGS += -m32
endif

ifeq ($(DEBUG),1)
LIBS_FLAGS += -g
CFLAGS += -DDEBUG -g
else
CFLAGS += -O
endif

ifeq ($(TARGET_PC), 1)
CFLAGS += -DTARGET_PC -D_XOPEN_SOURCE=600
endif

CFLAGS += $(INCLUDE_CFLAGS)

LDFLAGS := -Map $(NAME).map


#default:
#	$(CC) -c $(CFLAGS) $(C_FILES) -Llib -l:miniaudio.a -lm -ldl -lpthread
#	$(LD) $(LDFLAGS) -o $(OUTPUT) $(BUILD_DIR)$(O_FILES) 


default:
	$(CC) $(CFLAGS) $(C_FILES) -o $(OUTPUT) -Llib -l:miniaudio.a -lm -ldl -lpthread

dirs:
	mkdir -p

libs:
	$(CC) $(LIBS_FLAGS) -c lib/miniaudio.c -o lib/miniaudio.o
	$(AR) cr lib/miniaudio.a ./lib/miniaudio.o
	
strip:
	$(shell strip $(OUTPUT)) 

clean:
	$(RM) $(OUTPUT)
	
