#include <stdio.h>
#include "tiny_spec/spec.h"
#include "sopp.h"


it (identifies_a_short_option) {
	static char *const args[] = {"-A"};
	void *options = sopp_init(1, (void *)args, sopp_list(
		sopp_opt('a', sopp_s('A'), NULL)
	));

	is_equal( sopp_is_set(options, 'a'), 1 );
}


it (does_not_identify_a_short_option) {
	static char *const args[] = {"-B"};
	void *options = sopp_init(1, (void *)args, sopp_list(
		sopp_opt('a', sopp_s('A'), NULL)
	));

	is_not_equal( sopp_is_set(options, 'a'), 1 );
}


it (identifies_combined_short_options) {
	static char *const args[] = {"-abc"};
	void *options = sopp_init(1, (void *)args, sopp_list(
		sopp_opt('a', sopp_s('a'), NULL),
		sopp_opt('b', sopp_s('b'), NULL),
		sopp_opt('c', sopp_s('c'), NULL)
	));

	is_equal( sopp_is_set(options, 'a'), 1 );
	is_equal( sopp_is_set(options, 'b'), 1 );
	is_equal( sopp_is_set(options, 'c'), 1 );
}



it (identifies_a_long_option) {
	static char *const args[] = {"--long_option"};
	void *options = sopp_init(1, (void *)args, sopp_list(
		sopp_opt('l', NULL, sopp_l("long_option"))
	));

	is_equal( sopp_is_set(options, 'l'), 1 );
}


it (finds_an_argument_for_a_short_option) {
	static char *const args[] = {"-f", "my_file"};
	void *options = sopp_init(2, (void *)args, sopp_list(
		sopp_opt('f', sopp_s('f'), NULL)
	));

	string_is_equal( sopp_arg(options, 'f'), "my_file" );
}


it (finds_an_argument_for_a_long_option) {
	static char *const args[] = {"--file", "my_file"};
	void *options = sopp_init(2, (void *)args, sopp_list(
		sopp_opt('f', NULL, sopp_l("file"))
	));

	string_is_equal( sopp_arg(options, 'f'), "my_file" );
}


it (finds_an_argument_for_the_last_option_in_combined_short_options) {
	static char *const args[] = {"-vaf", "my_file"};
	void *options = sopp_init(2, (void *)args, sopp_list(
		sopp_opt('v', sopp_s('v'), NULL),
		sopp_opt('a', sopp_s('a'), NULL),
		sopp_opt('f', sopp_s('f'), NULL)
	));

	string_is_equal( sopp_arg(options, 'f'), "my_file" );
}

it (ignores_extra_options) {
	static char *const args[] = {"-vaf"};
	void *options = sopp_init(1, (void *)args, sopp_list(
		sopp_opt('f', sopp_s('f'), NULL)
	));

	is_equal( sopp_is_set(options, 'f'), 1 );
}

it (handles_non_existing_options) {
	static char *const args[] = {"-f"};
	void *options = sopp_init(1, (void *)args, sopp_list(
		sopp_opt('f', sopp_s('f'), NULL)
	));

	sopp_is_set(options, 'a'); /* should not throw an exception */
}

it (handles_several_non_existing_options) {
	static char *const args[] = {"-f"};
	void *options = sopp_init(1, (void *)args, sopp_list(
		sopp_opt('a', sopp_s('a'), NULL),
		sopp_opt('b', sopp_s('b'), NULL),
		sopp_opt('f', sopp_s('f'), NULL)
	));

	sopp_is_set(options, 'x'); /* should not throw an exception */
}

it (handles_arguments_to_non_existing_options) {
	static char *const args[] = {"-f", "file"};
	void *options = sopp_init(2, (void *)args, sopp_list(
		sopp_opt('f', sopp_s('f'), NULL)
	));

	is_equal(sopp_arg(options, 'a'), NULL); /* should not throw an exception */
}

start_spec(sopp)
	example(identifies_a_short_option)
	example(identifies_combined_short_options)
	example(does_not_identify_a_short_option)
	example(identifies_a_long_option)
	example(finds_an_argument_for_a_short_option)
	example(finds_an_argument_for_a_long_option)
	example(finds_an_argument_for_the_last_option_in_combined_short_options)
	example(ignores_extra_options)
	example(handles_non_existing_options)
	example(handles_arguments_to_non_existing_options)
	example(handles_several_non_existing_options)
end_spec


int main(int argc, char **argv) {
	return verify_spec(sopp);
}
