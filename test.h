
#define it(desc) void desc (void *_context)


typedef void (*spec)(void *);
typedef struct { const char *name; spec spec; } test_description;
#define test(name) { #name, name },
#define start_suite(name) const test_description name[] = {
#define end_suite {0, 0} };

int run_suite(const test_description* suite);

#define should_be_true(thing) __should_be_true(_context, #thing, (void *)thing);
void __should_be_true(void *context, char *desc, void *thing);

#define should_be_false(thing) __should_be_false(_context, #thing, (void *)thing);
void __should_be_false(void *context, char *desc, void *thing);

#define should_be_null(thing) __should_be_null(_context, #thing, (void *)thing);
void __should_be_null(void *context, char *desc, void *thing);

#define should_be_equal(thing1, thing2) __should_be_equal(_context, #thing1, (void *)thing1, #thing2, (void *)thing2);
void __should_be_equal(void *context, char *desc1, void *thing1, char *desc2, void *thing2);
