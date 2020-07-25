CFLAGS = -Wall -Wpedantic -Werror --std=c11

OBJS = main.o
OBJS := $(OBJS:%.o=src/%.o)

.PHONY: all
all: licp

.PHONY: clean
clean:
	rm -f $(OBJS) licp

licp: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
