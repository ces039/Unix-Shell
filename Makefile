all: gshell

dnode.o: dnode.c dnode.h
	gcc -std=gnu99 -c dnode.c -o dnode.o

dlist.o: dlist.c dlist.h dnode.h
	gcc -std=gnu99 -c dlist.c -o dlist.o

wrappers.o: wrappers.c wrappers.h
	gcc -std=gnu99 -c wrappers.c -o wrappers.o

gshell: gshell.c wrappers.o dlist.o dnode.o
	gcc -std=gnu99 gshell.c wrappers.o dlist.o dnode.o -o gshell

.PHONY: clean
clean:
	/bin/rm -rf gshell

