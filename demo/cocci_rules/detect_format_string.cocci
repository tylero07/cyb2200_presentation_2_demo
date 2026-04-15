// Rule: detect_format_string.cocci
// DETECT mode — finds printf(var) where the format string is a variable, not a literal
//
// Run: spatch --sp-file cocci_rules/detect_format_string.cocci c_files/vulnerable.c

@@
expression E;
@@

* printf(E);
