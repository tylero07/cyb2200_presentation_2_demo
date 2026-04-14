// Rule: detect_sprintf.cocci
// DETECT mode — flags sprintf() calls (unbounded formatted write)
// sprintf() has no size limit on the destination buffer
// Covered in: CYB2200 L3 Unbounded String Functions (sprintf section)
//
// Run: spatch --sp-file detect_sprintf.cocci vulnerable.c

@@
expression dst, fmt;
expression list args;
@@

* sprintf(dst, fmt, args);
