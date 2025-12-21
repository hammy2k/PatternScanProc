CC      := x86_64-w64-mingw32-gcc
CFLAGS  := -Wall -Wextra -O0 -fno-asynchronous-unwind-tables
LDFLAGS := -shared -Wl,--exclude-all-symbols
TARGET  := ../bin/hidden.dll
SRC     := dllmain.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)

