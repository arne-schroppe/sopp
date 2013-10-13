#define SPEC_RUNNING

#define it(desc) void desc (void *_context)


typedef void (*example_func)(void *);
typedef struct { const char *name; example_func ex; } example;

typedef const example spec[];

#define example(name) { #name, name },
#define start_spec(name) spec name = {
#define end_spec {0, 0} };

#define verify_spec(name) __verify_spec(#name, name)
int __verify_spec(char *name, spec spec);




/* Built-in matchers */

#define is_true(subject) __is_true(_context, #subject, (void *)subject);
void __is_true(void *context, char *desc, void *subject);

#define is_false(subject) __is_false(_context, #subject, (void *)subject);
void __is_false(void *context, char *desc, void *subject);

#define is_null(subject) __is_null(_context, #subject, (void *)subject);
void __is_null(void *context, char *desc, void *subject);

#define is_equal(subject1, subject2) __is_equal(_context, #subject1, (void *)subject1, #subject2, (void *)subject2);
void __is_equal(void *context, char *desc1, void *subject1, char *desc2, void *subject2);

#define is_not_equal(subject1, subject2) __is_not_equal(_context, #subject1, (void *)subject1, #subject2, (void *)subject2);
void __is_not_equal(void *context, char *desc1, void *subject1, char *desc2, void *subject2);

