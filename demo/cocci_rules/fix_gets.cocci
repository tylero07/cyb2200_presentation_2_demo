// Rule: fix_gets.cocci
// PATCH mode — replaces gets(buf) with fgets(buf, sizeof(buf), stdin)
//
// Run (dry):  spatch --sp-file cocci_rules/fix_gets.cocci c_files/vulnerable.c
// Run (apply): spatch --sp-file cocci_rules/fix_gets.cocci --in-place c_files/vulnerable.c

@@
expression buf;
@@

- gets(buf);
+ fgets(buf, sizeof(buf), stdin);
