
#ifndef SOPP_H_INCLUDED
#define SOPP_H_INCLUDED

/*
   SOPP, the Simple OPtion Parser
*/

typedef enum  {
	INVALID = 0,
	SHORT = 1,
	LONG
} alias_type;

typedef union {
	char *l;
	char s;
} alias_identifier;

typedef struct {
	alias_type type;
	alias_identifier identifier;
} alias;


typedef struct {
  int key;
  const char *description;
	alias *aliases;
	int is_set;
	const char *argument;
} sopp_option;


typedef struct {
	sopp_option *options;
	int count;
} sopp_options;

#define sopp_s(ident) (alias){SHORT, {.s = ident} }
#define sopp_l(ident) (alias){LONG, {.l = ident} }
#define sopp_NULL  (sopp_option){0, NULL, NULL, 0, NULL}
#define sopp_list( ... ) (sopp_options[]){{ (sopp_option[]){ __VA_ARGS__, sopp_NULL }, 0 }}
#define sopp_opt(key, descr, ...)    { key, descr, (alias[]){ __VA_ARGS__, (alias){INVALID, 0} }, 0, NULL }

void *sopp_init(int argc, const char **argv, sopp_options *options);
int sopp_is_set(const void *options, int key);
const char *sopp_arg(const void *options, int key);
void sopp_print_help(const void *options);


#endif
