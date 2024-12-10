BINUTILS_PREFIX := 
CC := $(BINUTILS_PREFIX)gcc

DEBUG ?= 0


CFLAGS := -std=c99 -Wall -Wextra

ifeq ($(DEBUG), 1)
CFLAGS += -g -DDEBUG
else
CFLAGS += -O1
endif


OUTPUT := mkscript

C_FILES := main.c

default:
	$(CC) $(CFLAGS) $(C_FILES) -L../../lib -l:lz4.a -o $(OUTPUT)

clean:
	$(RM) $(OUTPUT)


