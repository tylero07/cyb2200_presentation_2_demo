// Rule: detect_gets.cocci
// DETECT mode — finds all calls to gets()
// gets() is ALWAYS unsafe: no size parameter, always causes buffer overflow risk
// Covered in: CYB2200 L5 Buffer Overflow
//
// Run: spatch --sp-file detect_gets.cocci vulnerable.c

@@
expression buf;
@@

* gets(buf);
