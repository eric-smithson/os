os: assgn1.o fcfs.o test.o rr.o
	gcc assgn1.o fcfs.o test.o rr.o

assgn1.o: assgn1.c assgn1.h
	gcc -c assgn1.c

fcfs.o: fcfs.c 
	gcc -c fcfs.c

test.0: test.c
