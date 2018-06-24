obj_path=../obj
exe=doublelist-1 doublelist-2
all:doublelist-1 doublelist-2
doublelist-1:doublelist-1.c
	gcc -g doublelist-1.c -I../include -o doublelist-1
doublelist-2:doublelist-2.c
	gcc -g doublelist-2.c -I../include -o doublelist-2

clean:
	rm -rf ${obj_path}/(wildcard *)
install:
	mv doublelist-1 ../exe
	mv doublelist-2 ../exe
