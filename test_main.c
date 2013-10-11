#include <stdio.h>
#include "test.h"



it( prints_a_string ) {
	should_be_true(1 - 1);
}

it( fails ) {
	should_be_true(0);
}



int main(int argc, char **argv) {

	start_suite(suite)
		test(prints_a_string),
		test(fails),
	end_suite

	run_suite(suite);
}
