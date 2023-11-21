# Macros
FILES=./src/main.c
CFLAGS=-Wall -Wextra -Wfloat-equal -Wshadow

# Targets

build: $(FILES)
	gcc $(FILES) -o ./build/file_sharing_c

run: build
	./build/file_sharing_c

