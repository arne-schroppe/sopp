#include "test.h"
#include <stdio.h>
#include <stdarg.h>

typedef struct {
	int success;
	const char *spec_desc;
} spec_context;


void test_result(void *ctx, int is_failing, char *fail_desc, ...) {
	spec_context *context = (spec_context *)ctx;

	if(!is_failing) return;

	if(context->success != 0) {
		printf("it %s:\n", context->spec_desc);
		context->success = 0;
	}

	printf("  ");
	va_list arg_ptr;
	va_start(arg_ptr, fail_desc);
	vprintf(fail_desc, arg_ptr);
	va_end(arg_ptr);
	printf("\n");

}

void __should_be_true(void *context, char *desc, void *thing) {
	test_result(context, !thing, "%s is not true", desc);
}

void __should_be_false(void *context, char *desc, void *thing) {
	test_result(context, !!thing, "%s is not false", desc);
}

void __should_be_null(void *context, char *desc, void *thing) {
	test_result(context, thing != NULL, "%s is not NULL", desc);
}

void __should_be_equal(void *context, char *desc1, void *thing1, char *desc2, void *thing2) {
	test_result(context, thing1 != thing2, "%s does not equal %s", desc1, desc2);
}

void __should_not_be_equal(void *context, char *desc1, void *thing1, char *desc2, void *thing2) {
	test_result(context, thing1 == thing2, "%s equals %s (but shouldn't)", desc1, desc2);
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

