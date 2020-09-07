CC = gcc
CFLAGS = -O0 -g -Wall -Werror

all: linked_list.o myls.h myls.c
	$(CC) $(CFLAGS) -o myls myls.c linked_list.o

linked_list.o: linked_list.c linked_list.h
	$(CC) $(CFLAGS) -c linked_list.c 

clean:
	rm -f *.o *~ qtest 
	rm -rf *.dSYM
	(cd traces; rm -f *~)

