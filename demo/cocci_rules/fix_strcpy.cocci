// Rule: fix_strcpy.cocci
// PATCH mode — replaces strcpy(dst, src) with strncpy(dst, src, sizeof(dst)-1)
// strncpy() is the bounded safe alternative; n limits how many bytes are copied
// Covered in: CYB2200 L4 Bounded String Functions
//
// Run (dry):  spatch --sp-file fix_strcpy.cocci vulnerable.c
// Run (apply): spatch --sp-file fix_strcpy.cocci --in-place vulnerable.c

@@
expression dst, src;
@@

- strcpy(dst, src);
+ strncpy(dst, src, sizeof(dst) - 1);
+ dst[sizeof(dst) - 1] = '\0';
