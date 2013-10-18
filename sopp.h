
#ifndef SOPP_H_INCLUDED
#define SOPP_H_INCLUDED

/*
   SOPP, the Simple OPtion Parser
*/

typedef struct {
  int key;
  const char *short_opts;
  const char **long_opts;
  const char *description;
	int is_set;
	const char *argument;
} sopp_option;


typedef struct {
	sopp_option *options;
	int count;
} sopp_options;

#define sopp_NULL  (sopp_option){0, 0, 0, 0, 0, 0}
#define sopp_list( ... ) (sopp_options[]){{ (sopp_option[]){ __VA_ARGS__, sopp_NULL }, 0 }}
#define sopp_opt(key, shorts, longs, descr)    { key, shorts, longs, descr, 0, NULL }
#define sopp_s( ... )      (const char*)(const char[]){ __VA_ARGS__, 0 }
#define sopp_l( ... )       (const char**)(const char*[]){ __VA_ARGS__, NULL }

void *sopp_init(int argc, const char **argv, sopp_options *options);
int sopp_is_set(const void *options, int key);
const char *sopp_arg(const void *options, int key);
void sopp_print_description(const void *options);


#endif
