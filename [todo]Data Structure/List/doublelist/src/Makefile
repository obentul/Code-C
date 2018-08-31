obj_path=../obj
exe=doublelist
all:doublelist
doublelist:doublelist.c
	gcc -g doublelist.c main.c -I../include -o doublelist
lib:doublelist.c
	gcc -c -g doublelist.c -I../include -o doublelist.o

clean:
	rm -rf ${obj_path}/(wildcard *)
install:
	mv doublelist ../exe
	mv doublelist.o ../lib
