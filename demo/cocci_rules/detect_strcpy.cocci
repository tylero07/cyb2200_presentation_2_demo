// Rule: detect_strcpy.cocci
// DETECT mode — flags all calls to strcpy()
//
// Run: spatch --sp-file cocci_rules/detect_strcpy.cocci c_files/vulnerable.c

@@
expression dst, src;
@@

* strcpy(dst, src);
