
#ifndef SOPP_H_INCLUDED
#define SOPP_H_INCLUDED

/*
   Simple OPtion Parser
*/

typedef struct {
  int key;
  int flags;
  const char *short_opts;
  const char **long_opts;
} sopp_opt;


#define sopp_list( ... ) (const void *)(sopp_opt[]){ __VA_ARGS__, {0, 0, 0, 0} }
#define sopp_option(key, flags, shorts, longs)    { key, flags, shorts, longs }
#define sopp_s( ... )      (const char*)(const char[]){ __VA_ARGS__, 0 }
#define sopp_l( ... )       (const char**)(const char*[]){ __VA_ARGS__, NULL }

void *sopp_init(int argc, const char **argv, const void *options);
size_t sopp_count(const void *options, int key);
char *sopp_arg(const void *options, int key);


#endif
