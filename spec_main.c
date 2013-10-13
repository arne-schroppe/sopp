#include <stdio.h>
#include "micro_spec/spec.h"
#include "sopp.h"


it (identifies_a_short_option) {

	static char *const args[] = {"-A"};
	void *options = sopp_init(1, (void *)args, sopp_list(
		sopp_opt('a', 0, sopp_s('A'), NULL)
	));

	is_equal( sopp_is_set(options, 'a'), 1 );
}


it (does_not_identify_a_short_option) {

	static char *const args[] = {"-B"};
	void *options = sopp_init(1, (void *)args, sopp_list(
		sopp_opt('a', 0, sopp_s('A'), NULL)
	));

	is_not_equal( sopp_is_set(options, 'a'), 1 );
}


it (identifies_a_long_option) {

	static char *const args[] = {"--long_option"};
	void *options = sopp_init(1, (void *)args, sopp_list(
		sopp_opt('l', 0, NULL, sopp_l("long_option"))
	));

	is_equal( sopp_is_set(options, 'l'), 1 );
}

start_spec(sopp)
	example(identifies_a_short_option)
	example(does_not_identify_a_short_option)
	example(identifies_a_long_option)
end_spec

int main(int argc, char **argv) {
	return verify_spec(sopp);
}
