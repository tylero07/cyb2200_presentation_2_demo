// Rule: fix_malloc_null_check.cocci
// PATCH mode — inserts a NULL check after every malloc() assignment.
//
// Run (dry):   spatch --sp-file cocci_rules/fix_malloc_null_check.cocci c_files/vulnerable.c
// Run (apply): spatch --sp-file cocci_rules/fix_malloc_null_check.cocci --in-place c_files/vulnerable.c

@@
type T;
T *ptr;
expression sz;
@@

  ptr = malloc(sz);
+ if (ptr == NULL) { perror("malloc"); exit(1); }
