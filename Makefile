CC = clang
CFLAGS = -Wall -Wvla -Werror -g

.PHONY: asan msan nosan

asan: CFLAGS += -fsanitize=address,leak,undefined
asan: all

msan: CFLAGS += -fsanitize=memory,undefined -fsanitize-memory-track-origins
msan: all

nosan: all

.PHONY: all
all: main.c scanner.c parser.c tree.c interpreter.c
	$(CC) $(CFLAGS) -o lithium main.c scanner.c parser.c tree.c interpreter.c

.PHONY: clean
clean: 
	rm -f *.o lithium