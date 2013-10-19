#include <stdio.h>
#include <stdlib.h>
#include "tiny_spec/spec.h"
#include "sopp.h"

extern char* test_print_buffer;

void init_print_buffer();

#define with_print_buffer(block) \
	init_print_buffer(); \
  block \


it (identifies_a_short_option) {
	static char *const args[] = {"-A"};
	void *options = sopp_init(1, (void *)args, sopp_list(
		sopp_opt('a', 'A', NULL, NULL)
	));

	is_equal( sopp_is_set(options, 'a'), 1 );
}


it (does_not_identify_a_short_option) {
	static char *const args[] = {"-B"};
	void *options = sopp_init(1, (void *)args, sopp_list(
		sopp_opt('a', 'A', NULL, NULL)
	));

	is_not_equal( sopp_is_set(options, 'a'), 1 );
}


it (identifies_combined_short_options) {
	static char *const args[] = {"-abc"};
	void *options = sopp_init(1, (void *)args, sopp_list(
		sopp_opt('a', 'a', NULL, NULL),
		sopp_opt('b', 'b', NULL, NULL),
		sopp_opt('c', 'c', NULL, NULL)
	));

	is_equal( sopp_is_set(options, 'a'), 1 );
	is_equal( sopp_is_set(options, 'b'), 1 );
	is_equal( sopp_is_set(options, 'c'), 1 );
}



it (identifies_a_long_option) {
	static char *const args[] = {"--long_option"};
	void *options = sopp_init(1, (void *)args, sopp_list(
		sopp_opt('l', 0, "long_option", NULL)
	));

	is_equal( sopp_is_set(options, 'l'), 1 );
}


it (finds_an_argument_for_a_short_option) {
	static char *const args[] = {"-f", "my_file"};
	void *options = sopp_init(2, (void *)args, sopp_list(
		sopp_opt('f', 'f', NULL, NULL)
	));

	string_is_equal( sopp_arg(options, 'f'), "my_file" );
}


it (finds_an_argument_for_a_long_option) {
	static char *const args[] = {"--file", "my_file"};
	void *options = sopp_init(2, (void *)args, sopp_list(
		sopp_opt('f', 0, "file", NULL)
	));

	string_is_equal( sopp_arg(options, 'f'), "my_file" );
}


it (finds_an_argument_for_the_last_option_in_combined_short_options) {
	static char *const args[] = {"-vaf", "my_file"};
	void *options = sopp_init(2, (void *)args, sopp_list(
		sopp_opt('v', 'v', NULL, NULL),
		sopp_opt('a', 'a', NULL, NULL),
		sopp_opt('f', 'f', NULL, NULL)
	));

	string_is_equal( sopp_arg(options, 'f'), "my_file" );
}


it (ignores_extra_options) {
	static char *const args[] = {"-vaf"};
	void *options = sopp_init(1, (void *)args, sopp_list(
		sopp_opt('f', 'f', NULL, NULL)
	));

	is_equal( sopp_is_set(options, 'f'), 1 );
}


it (handles_non_existing_options) {
	static char *const args[] = {"-f"};
	void *options = sopp_init(1, (void *)args, sopp_list(
		sopp_opt('f', 'f', NULL, NULL)
	));

	sopp_is_set(options, 'a'); /* should not throw an exception */
}


it (handles_several_non_existing_options) {
	static char *const args[] = {"-f"};
	void *options = sopp_init(1, (void *)args, sopp_list(
		sopp_opt('a', 'a', NULL, NULL),
		sopp_opt('b', 'b', NULL, NULL),
		sopp_opt('f', 'f', NULL, NULL)
	));

	sopp_is_set(options, 'x'); /* should not throw an exception */
}


it (handles_arguments_to_non_existing_options) {
	static char *const args[] = {"-f", "file"};
	void *options = sopp_init(2, (void *)args, sopp_list(
		sopp_opt('f', 'f', NULL, NULL)
	));

	is_equal(sopp_arg(options, 'a'), NULL); /* should not throw an exception */
}



it (prints_a_description_for_a_short_option) {
	static char *const args[] = {};
	void *options = sopp_init(0, (void *)args, sopp_list(
		sopp_opt('a', 'f', NULL, "The file to process")
	));

  with_print_buffer({
	  sopp_print_help(options);
	  string_is_equal(test_print_buffer, "-f\tThe file to process\n");
  });
}

it (prints_a_description_for_a_long_option) {
	static char *const args[] = {};
	void *options = sopp_init(0, (void *)args, sopp_list(
		sopp_opt('f', 0, "file", "The file to process")
	));

  with_print_buffer({
	  sopp_print_help(options);
	  string_is_equal(test_print_buffer, "--file\tThe file to process\n");
  });
}

it (prints_a_description_for_long_and_short_options) {

	static char *const args[] = {};
	void *options = sopp_init(0, (void *)args, sopp_list(
		sopp_opt('f', 'f', "file", "The file to process")
	));

  with_print_buffer({
	  sopp_print_help(options);
	  string_is_equal(test_print_buffer, "-f, --file\tThe file to process\n");
  });
}


it (prints_descriptions_for_several_short_options) {

	static char *const args[] = {};
	void *options = sopp_init(0, (void *)args, sopp_list(
		sopp_opt('d', 'd', NULL, "A directory with settings"),
		sopp_opt('f', 'f', NULL, "The file to process")
	));

  with_print_buffer({
	  sopp_print_help(options);
	  string_is_equal(test_print_buffer, "-d\tA directory with settings\n-f\tThe file to process\n");
  });
}


it (prints_descriptions_for_several_long_options) {

	static char *const args[] = {};
	void *options = sopp_init(0, (void *)args, sopp_list(
		sopp_opt('d', 0, "dir", "A directory with settings"),
		sopp_opt('f', 0, "file", "The file to process")
	));

  with_print_buffer({
	  sopp_print_help(options);
	  string_is_equal(test_print_buffer, "--dir\tA directory with settings\n--file\tThe file to process\n");
  });
}


it (does_not_print_anything_if_no_description_is_given) {

	static char *const args[] = {};
	void *options = sopp_init(0, (void *)args, sopp_list(
		sopp_opt('d', 0, "dir", "A directory with settings"),
		sopp_opt('f', 0, "file", NULL)
	));

  with_print_buffer({
	  sopp_print_help(options);
	  string_is_equal(test_print_buffer, "--dir\tA directory with settings\n");
  });
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

	example(prints_a_description_for_a_short_option)
	example(prints_a_description_for_a_long_option)
	example(prints_a_description_for_long_and_short_options)
	example(prints_descriptions_for_several_short_options)
	example(prints_descriptions_for_several_long_options)
	example(does_not_print_anything_if_no_description_is_given)
end_spec


int main(int argc, char **argv) {
	return verify_spec(sopp);
}
