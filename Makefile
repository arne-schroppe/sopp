
CC=clang
TEST_NAME=spec


test:
	CC -o $(TEST_NAME) -DTINY_SPEC sopp.c spec_main.c tiny_spec/spec.c
	./$(TEST_NAME)
