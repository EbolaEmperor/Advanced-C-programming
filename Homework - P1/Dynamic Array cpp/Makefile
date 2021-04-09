CC = g++
SRC = src
CFLAG = -I $(SRC)
OBJS = main.o $(SRC)/array.o

test: $(OBJS)
	$(CC) $(CFLAG) $(OBJS) -o $@

.cpp.o:
	$(CC) $(CFLAG) -c $< -o $@

clean:
	rm $(OBJS) test
