exe=main1
all:main1
main1:main1.c
  gcc -pthread -g main1.c -I../include -o main1
lib:mythread.o
  gcc -c -pthread -g main1.c -I../include -o mythread.o
clean:
  rm -rf ${exe}
  rm -rf ../lib/*
install:
  mv main1 ../exe
  mv mythread.o ../lib
