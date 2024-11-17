OUTPUT := VN.elf
TARGET_PC ?= 1
NO64BIT ?= 1

DEBUG ?= 0

BINUTILS_PREFIX := 
CC := $(BINUTILS_PREFIX)gcc

VNLIB := vnlib
SRC_DIRS := $(shell find example/src -type d)

VNLIB_FILES := $(foreach dir,$(VNLIB),$(wildcard $(dir)/*.c))


C_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

C_FILES += $(VNLIB_FILES)



INCLUDE_CFLAGS = -I . -I example/include -I $(VNLIB)

CFLAGS:= -std=c99 

ifeq ($(NO64BIT), 1)
CFLAGS += -m32
endif

ifeq ($(DEBUG),1)
CFLAGS += -DDEBUG -g
else
CFLAGS += -O
endif

ifeq ($(TARGET_PC), 1)
CFLAGS += -DTARGET_PC -D_XOPEN_SOURCE=600
endif

CFLAGS += $(INCLUDE_CFLAGS)

default:
	$(CC) $(CFLAGS) $(C_FILES) -o $(OUTPUT)

strip:
	$(shell strip VN.elf) 

clean:
	$(RM) $(OUTPUT)
	