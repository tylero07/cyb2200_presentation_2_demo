// Rule: fix_format_string.cocci
// PATCH mode — wraps printf(var) with printf("%s", var)
// Forces the format string to be a literal, eliminating the attack surface
// Covered in: CYB2200 L7/L8 Format String Vulnerability
//
// Run (dry):  spatch --sp-file fix_format_string.cocci vulnerable.c
// Run (apply): spatch --sp-file fix_format_string.cocci --in-place vulnerable.c

@@
expression E;
@@

- printf(E);
+ printf("%s", E);
