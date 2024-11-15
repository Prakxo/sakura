OUTPUT := VN.elf

DEBUG ?= 0

BINUTILS_PREFIX := 
CC := $(BINUTILS_PREFIX)gcc

VNLIB := vnlib
SRC_DIRS := $(shell find example/src -type d)

VNLIB_FILES := $(foreach dir,$(VNLIB),$(wildcard $(dir)/*.c))


C_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

C_FILES += $(VNLIB_FILES)



INCLUDE_CFLAGS = -I . -I example/include -I $(VNLIB)

#school workaround lol
CFLAGS := -O2 -std=c99
#CFLAGS := -m32 -std=c99

ifeq ($(DEBUG),1)
CFLAGS += -DDEBUG -g
endif

CFLAGS += $(INCLUDE_CFLAGS)

default:
	$(CC) $(CFLAGS) $(C_FILES) -o $(OUTPUT)

strip:
	$(shell strip VN.elf) 
	
clean:
	$(RM) $(OUTPUT)
	