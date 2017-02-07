os: assgn1.o fcfs.o
	gcc assgn1.o fcfs.o

assgn1.o: assgn1.c fcfs.h
	gcc -c assgn1.c

fcfs.o: fcfs.c fcfs.h
	gcc -c fcfs.c

