#include "test.h"
#include <stdio.h>

typedef struct {
	int success;
	const char *spec_desc;
} spec_context;


void test_failed(void *ctx) {
	spec_context *context = (spec_context *)ctx;
	if(context->success == 0) return;

	printf("'it %s' failed:\n", context->spec_desc);
	context->success = 0;
}

void __should_be_true(void *context, char *desc, void *thing) {
	if(!thing) {
		test_failed(context);
		printf("  %s is not true\n", desc);
	}
}

void __should_be_false(void *context, char *desc, void *thing) {
	if(thing) {
		test_failed(context);
		printf("  %s is not false\n", desc);
	}
}

void __should_be_null(void *context, char *desc, void *thing) {
	if(thing != NULL) {
		test_failed(context);
		printf("  %s is not NULL\n", desc);
	}
}

void __should_be_equal(void *context, char *desc1, void *thing1, char *desc2, void *thing2) {
	if(thing1 != thing2) {
		test_failed(context);
		printf("  %s does not equal %s\n", desc1, desc2);
	}
}

int run_suite(const test_description* suite) {
	
	int i = 0;
	spec_context context = {0, 0};
	spec current_test;
	while(1) {
		current_test = suite[i].spec;
		if(current_test == 0) break;

		context.success = 1;
		context.spec_desc = suite[i].name;
		current_test(&context);

		++i;
	}

	return 0;
}

