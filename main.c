#include <stdio.h>
#include "sopp.h"

typedef void (*func_t)();

int main(int argc, const char **argv) {

  void *options = sopp_init(argc, argv, sopp_list(
        sopp_option('a', 0, sopp_shorts('a'), sopp_longs("another_option")),
        sopp_option('b', 0, sopp_shorts('b'), sopp_longs("second_option"))
  ));


  if( sopp_count( options, 'a' ) ) {
    printf("option a given");
  }



  if( sopp_count( options, 'b' ) ) {
    printf("option b given");
  }

  return 0;
}
