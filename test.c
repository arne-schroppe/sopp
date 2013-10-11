#include "test.h"
#include <stdio.h>

void __should_be_true(void *context, char *desc, void *thing) {
	if(!thing) {
		printf("%s is not true\n", desc);
		int *success = context;
		*success = 0;
	}
}

int run_suite(const test_description* suite) {
	
	int i = 0;
	int success = 0;
	spec current_test;
	while(1) {
		current_test = suite[i].spec;
		if(current_test == 0) break;

		success = 1;
		current_test(&success);
		if(!success) {
			printf("FAILED: %s\n", suite[i].name);
		}

		++i;
	}

	return 0;
}

