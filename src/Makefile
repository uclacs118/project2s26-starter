CC=gcc
CPPFLAGS=-Wall -Wextra
LDFLAGS=-s
LDLIBS=

DEPS=io.o transport.o

all: server client 

server: server.o $(DEPS)
client: client.o $(DEPS)

clean:
	@find . -type f \
		! -name "*.c" \
		! -name "*.h" \
		! -name "*.cpp" \
		! -name "*.hpp" \
		! -name "Makefile" \
		! -name "README.md" -delete
	@find . -type d \( ! -name "." \) -exec rm -rf {} +
