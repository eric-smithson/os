os: assgn1.o fcfs.o sjf.o rr.o
	gcc assgn1.o fcfs.o sjf.o rr.o -o assgn1.out

assgn1.o: assgn1.c assgn1.h
	gcc -c assgn1.c

fcfs.o: fcfs.c 
	gcc -c fcfs.c

sjf.o: sjf.c 
	gcc -c sjf.c

rr.o: rr.c
	gcc -c rr.c	
