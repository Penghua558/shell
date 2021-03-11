TempOBJ = wish.o shellmisc.o paraexec.o checkexec.o
FinalOBJ = wish
CC = gcc
CFLAGS = -g

$(FinalOBJ): $(TempOBJ)
	$(CC) $(CFLAGS) $^ -o $@
%.o: %.c
	$(CC) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o
