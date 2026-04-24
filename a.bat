gcc -c main.c -o main.o
gcc -c header.c -o header.o
gcc main.o header.o -o start.exe
start.exe