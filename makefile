# Macros
FILES=./src/main.c ./src/server/server.c
CFLAGS=-Wall -Wextra -Wfloat-equal -Wshadow -Iinclude

# Targets

build: $(FILES)
	gcc $(CFLAGS) $(FILES) -o ./build/file_sharing_c

run: build
	./build/file_sharing_c

