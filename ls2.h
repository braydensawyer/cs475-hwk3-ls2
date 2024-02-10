#ifndef LS2_H_INCLUDED
#define LS2_H_INCLUDED

#include "stack.h"

#define TRUE 1
#define FALSE 0
#define INDENT "    "

char * fullPathName(char* path, char* name); 

void m1(char path[], stack_t *s, int indent); 

int m2(char path[], char target[], stack_t *s, int indent);

#endif
