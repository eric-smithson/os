os: assgn1.o fcfs.o test.o sjf.o
	gcc assgn1.o fcfs.o test.o sjf.o

assgn1.o: assgn1.c assgn1.h
	gcc -c assgn1.c

fcfs.o: fcfs.c 
	gcc -c fcfs.c

sjf.o: sjf.c 
	gcc -c sjf.c

test.0: test.c
