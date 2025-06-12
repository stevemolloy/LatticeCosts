CC=gcc
CFLAGS = -Wall -Wpedantic -Wextra -Wshadow -Wvla -std=c99 -ggdb
ifeq ($(CC), clang)
	CFLAGS +=  -fsanitize=undefined,address
endif
CINCLUDES =
CLIBS = -lxlsxio_read -lm

SRC = src
OBJ = objs

SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

BINDIR = bin
BIN = $(BINDIR)/lattice_cost

all: $(BIN)

$(BIN): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CINCLUDES) $^ -o $@ $(CLIBS)

$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@

clean:
	rm -rf $(BINDIR) $(OBJ)

run: $(BIN)
	$(BIN) ./data/LatticeSummaries.xlsx

