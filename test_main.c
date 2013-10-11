#include <stdio.h>
#include "test.h"
#include "sopp.h"


int somefunc(int a, int b) {
	return 0;
}


it (reads_a_short_option) {

	static char *const args[] = {"-a"};
	void *options = sopp_init(1, (void *)args, sopp_list(
		sopp_option('a', 0, sopp_s('a'), NULL)
	));

	is_equal( sopp_count(options, 'a'), 1 );
}

it (does_not_have_a_short_option) {

	static char *const args[] = {"-b"};
	void *options = sopp_init(1, (void *)args, sopp_list(
		sopp_option('a', 0, sopp_s('a'), NULL)
	));

	is_not_equal( sopp_count(options, 'a'), 1 );
}


int main(int argc, char **argv) {

	start_suite(suite)
		test(reads_a_short_option)
		test(does_not_have_a_short_option)
	end_suite

	run_suite(suite);
}
