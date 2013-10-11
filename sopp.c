#include <unistd.h>
#include <stdlib.h>
#include "sopp.h"

#include <stdio.h>


typedef struct {



} sopp_option_list;


/*

	 options = long | short
	 long = "--", long_opt, [argument]
	 long_opt = char+
	 argument = char+

	 short = "-", short_opt, {short_opt}, [argument]
*/


void option(const char *token, int *stop) {

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
		printf("Short option: %c\n", token[i]);
		++i;
	}

}

void argument(const char *token) {
	
}

void *sopp_init(int argc, const char **argv, const void *raw_options) {

	int i;
	int stop = 0;
	for(i = 0; i < argc; ++i) {

		if(argv[i][0] == '-') {
			option(&(argv[i][1]), &stop);
		}
		else {
			argument(argv[i]);
		}

		if(stop) {
			break;
		}
	}

  return NULL;
}


size_t sopp_count(const void *opts, char key) {
  return 0;
}


char *sopp_arg(const void *opts, char key) {
  return 0;
}
