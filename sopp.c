#include "sopp.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef TINY_SPEC
	#include <stdarg.h>

	char *test_print_buffer = NULL;
	size_t test_buffer_num_chars = 0;

	void init_print_buffer() {
		free(test_print_buffer);
		test_print_buffer = (char *)calloc(1000, sizeof(char));
		test_buffer_num_chars = 0;
	}

	void print_to_buffer(char *format, ...) {
		if(test_print_buffer == NULL) {
			return;
		}

	  va_list args;
	  va_start(args, format);
	  test_buffer_num_chars += vsprintf(test_print_buffer + test_buffer_num_chars, format, args);
	  va_end(args);
	}

	#define printf(...) print_to_buffer(__VA_ARGS__)

#endif

void set_short_option(sopp_options *options, const char short_opt, sopp_option **last_option) {
	int i;
	for( i = 0; i < options->count; ++i ) {
		sopp_option *option = &options->options[i];
		alias *alias = option->aliases;
		while(alias->type != INVALID) {
			if(alias->type == SHORT && alias->identifier.s == short_opt) {
				option->is_set = 1;
				*last_option = option;
			}
			++alias;
		}
	}
}

void set_long_option(sopp_options *options, const char *long_opt, sopp_option **last_option) {
	int i;
	for( i = 0; i < options->count; ++i ) {
		sopp_option *option = &options->options[i];
		alias *alias = option->aliases;
		while(alias->type != INVALID) {
			if(alias->type == LONG && strcmp(alias->identifier.l, long_opt) == 0) {
				option->is_set = 1;
				*last_option = option;
			}
			++alias;
		}
	}
}


void parse_option(sopp_options *options, const char *token, sopp_option **last_option, int *stop) {

	if(token[0] == '\0') {
		return;
	}

	if(token[0] == '-') {
		/*
		if(token[1] == '\0') {
			*stop = 1;
			return;
		}
		*/

		set_long_option(options, token + 1, last_option);
		return;
	}

	int i = 0;
	while(token[i] != '\0') {
		set_short_option(options, token[i], last_option);
		++i;
	}
}

void parse_argument(const char *token, sopp_option *last_option) {
	if(last_option == NULL) return; /* TODO gather these as unknown options or something */
	last_option->argument = token;
}

int compare_keys(const void *opt1, const void *opt2) {
	return ((const sopp_option*)opt1)->key - ((const sopp_option*)opt2)->key;
}

void sort_options(sopp_options *options) {
	int count = 0;
	while(options->options[count].key != 0) {
		++count;
	}

	options->count = count;
	qsort(options->options, count, sizeof(sopp_option), compare_keys);
}

void *sopp_init(int argc, const char **argv, sopp_options *options) {

	int i;
	int stop = 0;

	sort_options(options);

	sopp_option *last_option = NULL;
	for(i = 0; i < argc; ++i) {

		if(argv[i][0] == '-') {
			parse_option(options, &(argv[i][1]), &last_option, &stop);
		}
		else {
			parse_argument(argv[i], last_option);
		}

		if(stop) {
			break;
		}
	}

	return options;
}


sopp_option *find_option_for_key(const void *opts, int key) {
	const sopp_options *options = opts;
	int i;
	for( i = 0; i < options->count; ++i ) {
		if( options->options[i].key == key) {
			return &options->options[i];
		}
	}

	return NULL;
}

/* TODO check for NULL */
int sopp_is_set(const void *opts, int key) {
	sopp_option *option = find_option_for_key(opts, key);
	if(option == NULL) {
		return 0;
	}
	return option->is_set;
}

const char *sopp_arg(const void *opts, int key) {
	sopp_option *option = find_option_for_key(opts, key);
	if(option == NULL) {
		return NULL;
	}
	return option->argument;
}

void print_alias(alias *alias) {
	switch(alias->type) {

		case SHORT:
			printf("-%c", alias->identifier.s);
			break;

		case LONG:
			printf("--%s", alias->identifier.l);
			break;
		
		case INVALID:
			/*This should not happen*/
			break;
	}
}

void print_option(sopp_option *option) {
	if(option->description == NULL) {
		return;
	}

	alias *alias = option->aliases;
	while(alias->type != INVALID) {
		print_alias(alias);
		if((alias+1)->type != INVALID) {
			printf(", ");
		}
		++alias;
	}

	printf("	%s\n", option->description);
}

void sopp_print_help(const void *opts) {
	const sopp_options *options = opts;
	sopp_option *option = options->options;
	while(option->key != 0) {
		print_option(option);
		++option;
	}
}
