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


it (identifies_combined_short_options) {
	static char *const args[] = {"-abc"};
	void *options = sopp_init(1, (void *)args, sopp_list(
		sopp_opt('a', 0, sopp_s('a'), NULL),
		sopp_opt('b', 0, sopp_s('b'), NULL),
		sopp_opt('c', 0, sopp_s('c'), NULL)
	));

	is_equal( sopp_is_set(options, 'a'), 1 );
	is_equal( sopp_is_set(options, 'b'), 1 );
	is_equal( sopp_is_set(options, 'c'), 1 );
}



it (identifies_a_long_option) {
	static char *const args[] = {"--long_option"};
	void *options = sopp_init(1, (void *)args, sopp_list(
		sopp_opt('l', 0, NULL, sopp_l("long_option"))
	));

	is_equal( sopp_is_set(options, 'l'), 1 );
}


it (finds_an_argument_for_a_short_option) {
	static char *const args[] = {"-f", "my_file"};
	void *options = sopp_init(2, (void *)args, sopp_list(
		sopp_opt('f', 0, sopp_s('f'), NULL)
	));

	string_is_equal( sopp_arg(options, 'f'), "my_file" );
}


it (finds_an_argument_for_a_long_option) {
	static char *const args[] = {"--file", "my_file"};
	void *options = sopp_init(2, (void *)args, sopp_list(
		sopp_opt('f', 0, NULL, sopp_l("file"))
	));

	string_is_equal( sopp_arg(options, 'f'), "my_file" );
}


it (finds_an_argument_for_the_last_option_in_combined_short_options) {
	static char *const args[] = {"-vaf", "my_file"};
	void *options = sopp_init(2, (void *)args, sopp_list(
		sopp_opt('v', 0, sopp_s('v'), NULL),
		sopp_opt('a', 0, sopp_s('a'), NULL),
		sopp_opt('f', 0, sopp_s('f'), NULL)
	));

	string_is_equal( sopp_arg(options, 'f'), "my_file" );
}

start_spec(sopp)
	example(identifies_a_short_option)
	example(identifies_combined_short_options)
	example(does_not_identify_a_short_option)
	example(identifies_a_long_option)
	example(finds_an_argument_for_a_short_option)
	example(finds_an_argument_for_a_long_option)
	example(finds_an_argument_for_the_last_option_in_combined_short_options)
end_spec

int main(int argc, char **argv) {
	return verify_spec(sopp);
}
