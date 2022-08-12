output: main.o sum.o sub.o routine1.o routine2.o
	gcc main.o sum.o sub.o routine1.o routine2.o -lpthread -o output
main.o: main.c sum.h sub.h routine1.h routine2.h
	gcc main.c -c
sum.o: sum.c
	gcc sum.c -c
sub.o: sub.c
	gcc sub.c -c 
routine1.o: routine1.c
	gcc routine1.c -c
routine2.o: routine2.c
	gcc routine2.c -c
clean:
	rm *.o output
run:
	./output
                  