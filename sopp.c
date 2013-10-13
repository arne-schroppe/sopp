#include "sopp.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


void set_short_option(sopp_options *options, const char short_opt) {
	
	int i;
	for( i = 0; i < options->count; ++i ) {
		sopp_option *option = &options->options[i];
		int j = 0;
		while(option->short_opts[j] != 0) {
			if(option->short_opts[j] == short_opt) {
				option->is_set = 1;
			}
			++j;
		}
	}

}

void parse_option(sopp_options *options, const char *token, int *stop) {

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

		printf("long option: %s\n", token+1);
		return;
	}


	int i = 0;
	while(token[i] != '\0') {
		set_short_option(options, token[i]);
		//printf("Short option: %c\n", token[i]);
		++i;
	}

}

void parse_argument(const char *token) {
	
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

	for(i = 0; i < argc; ++i) {

		if(argv[i][0] == '-') {
			parse_option(options, &(argv[i][1]), &stop);
		}
		else {
			parse_argument(argv[i]);
		}

		if(stop) {
			break;
		}
	}

  return options;
}

int sopp_is_set(const void *opts, int key) {
  const sopp_options *options = opts;
	int i;
	for( i = 0; i < options->count; ++i ) {
		if( options->options[i].key == key && options->options[i].is_set ) {
			return 1;
		}
	}

	return 0;
}

char *sopp_arg(const void *opts, int key) {
  return 0;
}
