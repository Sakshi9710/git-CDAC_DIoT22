targetoutput: main.c libbasic.a
	gcc -o targetoutput -L . main.o -lbasic
output: main.o add.o mul.o div.o sub.o
	gcc main.o add.o mul.o div.o sub.o -o output
main.o: main.c basic-header.h
	gcc main.c -c 
add.o: add.c
	gcc add.c -c
mul.o: mul.c
	gcc mul.c -c
sub.o: sub.c
	gcc sub.c -c
div.o: div.c
	gcc div.c -c
clean:
	rm *.o output
run:
	./output
