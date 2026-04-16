// Rule: detect_malloc_no_null_check.cocci
// DETECT mode — reports every malloc() whose result is stored in a typed pointer.
//
//
// Run: spatch --sp-file cocci_rules/detect_malloc_no_null_check.cocci c_files/vulnerable.c

@@
type T;
T *ptr;
expression sz;
@@

* ptr = malloc(sz);
