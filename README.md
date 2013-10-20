# sopp


The Simple OPtion Parser


## Example

```C
void *options = sopp_init(argc, argv, sopp_list(
  sopp_opt('d', "The output directory", sopp_s('o'), sopp_l("output"), sopp_l("output-dir")),
  sopp_opt('f', "The input file", sopp_s('f'), sopp_l("file"))
));
    
if( !sopp_is_set(options, 'f') ) {
  sopp_print_help(options);
  exit(1);
}
    
if( sopp_is_set(options, 'd') ) {
  char *dir = sopp_arg(options, 'd');
  use_output_dir(dir);
}
    
output_data( sopp_arg(options, 'f') );
```
