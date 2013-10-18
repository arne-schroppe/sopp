
CC=clang
TEST_NAME=spec


test:
	CC -Wno-int-to-void-pointer-cast -o $(TEST_NAME) -DTEST sopp.c spec_main.c tiny_spec/spec.c
	./$(TEST_NAME)
