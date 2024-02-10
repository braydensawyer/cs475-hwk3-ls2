#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "ls2.h"

/**
 * Main function
 * Usage: ls2 <path> [exact-match-pattern]
 */
int main(int argc, char* argv[]) {
	// stack stores the lines to print out
	stack_t *s = initstack();

	if (argv[1]==NULL) {
        printf("Usage: %s <path> [exact-match-pattern]\n", argv[0]);
    }
    else if(argv[2] == NULL){
		m1(argv[1], s, 0);

	}
	else {
		m2(argv[1], argv[2], s, 0);
	}

	// print stack
	printstack(s);

	// free up stack
	freestack(s);
	return 0;
}
