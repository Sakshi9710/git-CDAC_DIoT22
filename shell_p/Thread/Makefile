output: main.o sum.o mul.o div.o sub.o
	gcc main.o sum.o mul.o div.o sub.o -o output
main.o: main.c sum.h mul.h div.h sub.h
	gcc main.c -c 
sum.o: sum.c
	gcc sum.c -c
mul.o: mul.c
	gcc mul.c -c
clean:
	rm *.o output
run:
	./output