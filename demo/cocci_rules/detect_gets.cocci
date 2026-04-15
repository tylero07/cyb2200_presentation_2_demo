// Rule: detect_gets.cocci
// DETECT mode — finds all calls to gets()
//
// Run: spatch --sp-file cocci_rules/detect_gets.cocci c_files/vulnerable.c

@@
expression buf;
@@

* gets(buf);
