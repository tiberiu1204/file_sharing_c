# Macros
FILES_SERVER=./src/main_server.c ./src/server/server.c
FILES_CLIENT=./src/main_client.c ./src/client/client.c
CFLAGS=-Wall -Wextra -Wfloat-equal -Wshadow -Iinclude

# Targets

build_server: $(FILES_SERVER)
	gcc $(CFLAGS) $(FILES_SERVER) -o ./build/server

run_server: build_server
	./build/server

build_client: $(FILES_CLIENT)
	gcc $(CFLAGS) $(FILES_CLIENT) -o ./build/client

run_client: build_client
	./build/client

