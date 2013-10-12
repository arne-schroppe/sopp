#include <stdio.h>
#include "micro_spec/spec.h"
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

start_spec(sopp)
	example(reads_a_short_option)
	example(does_not_have_a_short_option)
end_spec

int main(int argc, char **argv) {
	return verify_spec(sopp);
}
