// Rule: fix_gets.cocci
// PATCH mode — replaces gets(buf) with fgets(buf, sizeof(buf), stdin)
// fgets() is the safe bounded alternative to gets()
// Covered in: CYB2200 L3/L4 String functions
//
// Run (dry):  spatch --sp-file fix_gets.cocci vulnerable.c
// Run (apply): spatch --sp-file fix_gets.cocci --in-place vulnerable.c

@@
expression buf;
@@

- gets(buf);
+ fgets(buf, sizeof(buf), stdin);
