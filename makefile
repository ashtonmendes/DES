hw5: hw5.o DES.o encrypt.o encrypt3.o decrypt.o decrypt3.o tablecheck.o utilities.o
	gcc -g -Wall hw5.o DES.o encrypt.o encrypt3.o decrypt.o decrypt3.o tablecheck.o utilities.o -o hw5

hw5.o: hw5.c
	gcc -g -Wall -c hw5.c

DES.o: DES.c
	gcc -g -Wall -c DES.c

encrypt.o: encrypt.c
	gcc -g -Wall -c encrypt.c

encrypt3.o: encrypt3.c
	gcc -g -Wall -c encrypt3.c

decrypt.o: decrypt.c
	gcc -g -Wall -c decrypt.c

decrypt3.o: decrypt3.c
	gcc -g -Wall -c decrypt3.c

tablecheck.o: tablecheck.c
	gcc -g -Wall -c tablecheck.c

utilities.o: utilities.c
	gcc -g -Wall -c utilities.c

clean:
	rm -f *.o hw5
