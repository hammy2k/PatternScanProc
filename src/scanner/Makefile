CC      := x86_64-w64-mingw32-gcc
TARGET  := ../bin/output.exe

SRCS    := main.c PatternScan.c GetModuleHandle.c

# ----------------------------
# Compiler / linker flags
# ----------------------------
CFLAGS  := -Wall -Wextra -O2 -masm=intel \
           -fno-stack-protector -fno-asynchronous-unwind-tables

LDFLAGS := -s

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean

