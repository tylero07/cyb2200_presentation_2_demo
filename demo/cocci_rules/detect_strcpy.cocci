// Rule: detect_strcpy.cocci
// DETECT mode — flags all calls to strcpy()
// strcpy() is an unbounded string function; does not check destination size
// Covered in: CYB2200 L3 Unbounded String Functions
//
// Run: spatch --sp-file detect_strcpy.cocci vulnerable.c

@@
expression dst, src;
@@

* strcpy(dst, src);
