CC=gcc
CCFLAGS= -Wall -Werror -g -std=c99
LIBFLAGS= 
SRC= main.c hzip.c  huffman_node.c huffman_build.c heap.c babfiles.c
OBJ= $(SRC:.c=.o)
EXEC= Hzip



all: $(EXEC)


$(EXEC): $(OBJ)
	$(CC)  $^ -o $@  $(LIBFLAGS)


%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $<

.depends:
	$(CC) -MM $(SRC) > .depends


-include .depends

clean:
	rm -f $(OBJ) $(EXEC) *.*~
