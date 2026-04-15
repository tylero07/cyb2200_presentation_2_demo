// Rule: detect_sprintf.cocci
// DETECT mode — flags sprintf() calls (unbounded formatted write)
//
// Run: spatch --sp-file cocci_rules/detect_sprintf.cocci c_files/vulnerable.c

@@
expression dst, fmt;
expression list args;
@@

* sprintf(dst, fmt, args);
