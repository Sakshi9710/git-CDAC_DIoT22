output: main.o libaddsub.so 
	gcc -o output -L . main.o libaddsub.so 
# libaddsub.so: add2no.o sub2no.o
# 	gcc -shared -o libaddsub.so add2no.o sub2no.o
main.o: main.c addsub.h
	gcc main.c -c 
add2no.o: add2no.c
	gcc -fPIC add2no.c -c
sub2no.o: sub2no.c
	gcc -fPIC sub2no.c -c
clean:
	rm *.o output
run:
	./output
