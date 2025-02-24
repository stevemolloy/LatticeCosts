CC=clang
CFLAGS = -Wall -Wpedantic -Wextra -Wshadow -Wvla -std=c99 -ggdb
ifeq ($(CC), clang)
	CFLAGS +=  -fsanitize=undefined,address
endif
CINCLUDES =
CLIBS = -lxlsxio_read

SRC = src
OBJ = objs

SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

BINDIR = bin
BIN = $(BINDIR)/lattice_cost

all: $(BIN)

$(BIN): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CINCLUDES) -D_DEFAULT_SOURCE $^ -o $@ $(CLIBS)

$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CINCLUDES) -D_DEFAULT_SOURCE -c $< -o $@

clean:
	rm -rf $(BINDIR) $(OBJ)

run: $(BIN)
	$(BIN)

