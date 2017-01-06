all: clean libhash.a app  ta

libhash.a: hash.c
	gcc -Wall -c hash.c -lm
	ar -cvq libhash.a hash.o
	ranlib libhash.a

app: 	app.c
	gcc -Wall -o app app.c -L. -lhash -lpthread -lm

ta: ta.c
	gcc -Wall -o ta ta.c -L. -lpthread

clean:
	rm -fr *.o *.a *~ a.out app ta  hash.o libhash.a
