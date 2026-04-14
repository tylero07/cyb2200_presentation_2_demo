// Rule: detect_format_string.cocci
// DETECT mode — finds printf(var) where the format string is a variable, not a literal
// This is the classic format string vulnerability from L7/L8
// If the user controls the input, they can use %n, %x, etc. to read/write memory
//
// Run: spatch --sp-file detect_format_string.cocci vulnerable.c

@@
expression E;
@@

* printf(E);
