#include<stdio.h>
#include "rr.h"
#include "assgn1.h"


void print_test(int quantium_time)
{
	printf("quantium time is %d\n", quantium_time);
}

void pass_struct_array(struct Process *p_array)
{
	printf("passes struct array: first struct process arrival time is %d\n", p_array[0]->arrival);
}
	

