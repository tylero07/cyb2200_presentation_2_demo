// Rule: fix_format_string.cocci
// PATCH mode — wraps printf(var) with printf("%s", var)
//
// Run (dry):  spatch --sp-file cocci_rules/fix_format_string.cocci c_files/vulnerable.c
// Run (apply): spatch --sp-file cocci_rules/fix_format_string.cocci --in-place c_files/vulnerable.c

@@
expression E;
@@

- printf(E);
+ printf("%s", E);
