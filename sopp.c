#include "sopp.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void set_short_option(sopp_options *options, const char short_opt, sopp_option **last_option) {
	int i;
	for( i = 0; i < options->count; ++i ) {
		sopp_option *option = &options->options[i];
		int j = 0;
		while(option->short_opts[j] != 0) {
			if(option->short_opts[j] == short_opt) {
				option->is_set = 1;
				*last_option = option;
			}
			++j;
		}
	}
}

void set_long_option(sopp_options *options, const char *long_opt, sopp_option **last_option) {
	int i;
	for( i = 0; i < options->count; ++i ) {
		sopp_option *option = &options->options[i];
		int j = 0;
		while(option->long_opts[j] != NULL) {
			if(strcmp(option->long_opts[j], long_opt) == 0) {
				option->is_set = 1;
				*last_option = option;
			}
			++j;
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
