#include <unistd.h>
#include <stdlib.h>
#include "sopp.h"

#include <stdio.h>

#define DEFAULT_SIZE 20

/*

	 options = long | short
	 long = "--", long_opt, [argument]
	 long_opt = char+
	 argument = char+

	 short = "-", short_opt, {short_opt}, [argument]
*/


typedef struct {
	int id;
	int is_set;
} option;

typedef struct {
	int count;
	option *options;
} parsed_options;

void parse_option(parsed_options *options, const char *token, int *stop) {

	if(token[0] == '\0') {
		return;
	}

	if(token[0] == '-') {
		if(token[1] == '\0') {
			printf("End of options\n");
			*stop = 1;
			return;
		}

		printf("long option: %s\n", token+1);
		return;
	}


	int i = 0;
	while(token[i] != '\0') {
		(options->options)[options->count] = (option){
			token[i],
			1
		};
		++(options->count);
		//printf("Short option: %c\n", token[i]);
		++i;
	}

}

void parse_argument(const char *token) {
	
}


void *sopp_init(int argc, const char **argv, const void *raw_options) {

	int i;
	int stop = 0;

	parsed_options *parsed_opts = (parsed_options *)malloc(sizeof(parsed_options));
	parsed_opts->count = 0;
	parsed_opts->options = (option *)malloc(sizeof(option) * DEFAULT_SIZE);

	for(i = 0; i < argc; ++i) {

		if(argv[i][0] == '-') {
			parse_option(parsed_opts, &(argv[i][1]), &stop);
		}
		else {
			parse_argument(argv[i]);
		}

		if(stop) {
			break;
		}
	}

  return parsed_opts;
}

size_t sopp_count(const void *opts, int key) {
  const parsed_options *options = opts;
	int i;
	for( i = 0; i < options->count; ++i ) {
		if( options->options[i].id == key && options->options[i].is_set ) {
			return 1;
		}
	}

	return 0;
}

char *sopp_arg(const void *opts, int key) {
  return 0;
}
