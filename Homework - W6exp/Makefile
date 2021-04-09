CC = gcc
CFLAG = -I. -L.
OBJS = main.o
LIBS = pstring
RUN = test

all: $(RUN)
	./$< $(MAGIC) result.txt <0.in >0.out

$(RUN): $(OBJS) lib$(LIBS).a
	$(CC) $(CFLAG) $< -l$(LIBS) -o $@
	
lib$(LIBS).a:
	make -C src
	
.c.o:
	$(CC) $(CFLAG) -c $^
	
clean:
	rm $(OBJS) $(RUN) lib$(LIBS).a 0.out
	
	