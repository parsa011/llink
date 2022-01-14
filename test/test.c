#include "../llist.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

#define DEFAULT "\033[0m"
#define FAILED "\033[0;31m"
#define SUCCESS "\033[0;32m"

typedef struct person_t person;

typedef struct person_t {
	L_LINK(person) link;
	char name[64];
} person;

bool test_set_next()
{
	person a;
	strcpy(a.name,"1"); 

	person b;
	strcpy(b.name,"2"); 
	L_LINK_SNEXT(&a,&b);

	return strcmp(L_LINK_NEXT(&a)->name,"2") == 0;
}

bool test_set_prev()
{
	person a;
	strcpy(a.name,"1"); 

	person b;
	strcpy(b.name,"2"); 
	L_LINK_SPREV(&b,&a);

	return strcmp(L_LINK_PREV(&b)->name,"1") == 0;
}

const char *test_functions_names[] = {
	"test set next",
	"test set prev"
};

bool (*test_functions[])() = {
	test_set_next,
	test_set_prev
};

void log_res(char *state,const char *fmt,...)
{
	printf("%s",state);
	char msg[256];
	va_list ap;
	va_start(ap,fmt);
	vsnprintf(msg,256,fmt,ap);
	va_end(ap);
	printf("result : %s%s",DEFAULT,msg);
	putchar('\n');
}

int main()
{
	int test_func_count = sizeof(test_functions) / sizeof(test_functions[0]);
	for (int i = 0;i < test_func_count;i++) {
		if ((*test_functions[i])() == true) {
			log_res(SUCCESS,"'%s' passed",test_functions_names[i]);
		} else {
			log_res(FAILED,"'%s' failed",test_functions_names[i]);
		}
	}
	return 0;
}
