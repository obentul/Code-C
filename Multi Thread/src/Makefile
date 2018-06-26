exe=demo1
all:demo1
demo1:demo1.c
	gcc -pthread -g demo1.c -I../include -o demo1
lib:mythread.c
	gcc -c -pthread -g demo1.c -I../include -o mythread.o
clean:
	rm -rf ${exe}
	rm -rf ../lib/*
install:
	mv demo1 ../exe
	mv mythread.o ../lib
