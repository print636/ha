
main.exe:main.o stack.o
	gcc main.o stack.o -o main.exe -lreadline
main.o:main.c
	gcc -c main.c -o main.o -lreadline
stack.o:stack.c
	gcc -c stack.c -o stack.o
	
clean:
	rm -f *.o
