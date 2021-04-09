CC = gcc
SRC = src
CFLAG = -I $(SRC)
OBJS = test.o $(SRC)/fib.o

test: $(OBJS)
	$(CC) $(CFLAG) $(OBJS) -o $@

.c.o:
	$(CC) $(CFLAG) -c $< -o $@

clean:
	rm -f $(OBJS) test
