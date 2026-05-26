GBDK      ?= /opt/gbdk
CC        := $(GBDK)/bin/lcc
CFLAGS    := -Iinclude -Ires -msm83:gb --std-c11 -autobank
ROM       := gbc-minecraft.gbc
SRCS      := $(wildcard src/*.c)
OBJS      := $(SRCS:.c=.o)

all: $(ROM)

$(ROM): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $

clean:
	rm -f src/*.o $(ROM)
