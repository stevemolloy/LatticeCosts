CC=clang
CFLAGS = -Wall -Wpedantic -Wextra -Wshadow -Wvla -std=c18 -ggdb
ifeq ($(CC), clang)
	CFLAGS +=  -fsanitize=undefined,address
endif
CINCLUDES = -I/home/smolloy/Code/MATLAB2022/extern/include
CLIBS = -L/home/smolloy/Code/MATLAB2022/bin/glnxa64 -lmat -lmx -Wl,-rpath,/home/smolloy/Code/MATLAB2022/bin/glnxa64 -lxlsxio_read

SRC = src
OBJ = objs

SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

BINDIR = bin
BIN = $(BINDIR)/test

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
	$(BIN)

