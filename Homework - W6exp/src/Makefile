CC = gcc
OBJS = pstring.o
INC = ..
OUT = ..
CFLAG = -l$(INC)

libpstring.a:$(OBJS)
	ar rcs $(OUT)/$@ $^

pstring.o: pstring.c $(INC)/pstring.h
	$(CC) $(CFLAG) -c $<

clean:
	rm $(OBJS)