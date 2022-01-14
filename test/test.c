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

void show_list(person *first)
{
	int indent = 0;
	for (; first != NULL; first = L_LINK_NEXT(first)) {
		for (int x = 0; x < indent; x++)
			putchar('\t');
		printf("%s\r\n",first->name);
		indent++;
	}
}

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

bool test_insert()
{
	person *a = malloc(sizeof(person));
	strcpy(a->name,"1"); 
	
	person *b = malloc(sizeof(person));
	strcpy(b->name,"2");

	person *c = malloc(sizeof(person));
	strcpy(c->name,"3"); 

	L_LINK_SNEXT(a,b);
	L_LINK_SPREV(b,a);
	L_LINK_INSERT(a,c);

	return strcmp(L_LINK_NEXT(a)->name,"3") == 0;
}

bool test_remove()
{
	person *a = malloc(sizeof(person));
	strcpy(a->name,"1"); 

	person *b = malloc(sizeof(person));
	strcpy(b->name,"2");

	person *c = malloc(sizeof(person));
	strcpy(c->name,"3"); 

	L_LINK_SNEXT(a,c);
	L_LINK_SPREV(c,a);
	L_LINK_INSERT(c,a);
	L_LINK_REMOVE(a);
	if (L_LINK_PREV(b) == NULL)
		return true;
	return false;
}

const char *test_functions_names[] = {
	"test set next",
	"test set prev",
	"test insert",
	"test remove"
};

bool (*test_functions[])() = {
	test_set_next,
	test_set_prev,
	test_insert,
	test_remove
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
