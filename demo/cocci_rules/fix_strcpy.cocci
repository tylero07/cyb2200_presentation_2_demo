// Rule: fix_strcpy.cocci
// PATCH mode — replaces strcpy(dst, src) with strncpy(dst, src, sizeof(dst)-1)
//
// Run (dry):  spatch --sp-file cocci_rules/fix_strcpy.cocci c_files/vulnerable.c
// Run (apply): spatch --sp-file cocci_rules/fix_strcpy.cocci --in-place c_files/vulnerable.c

@@
expression dst, src;
@@

- strcpy(dst, src);
+ strncpy(dst, src, sizeof(dst) - 1);
+ dst[sizeof(dst) - 1] = '\0';
