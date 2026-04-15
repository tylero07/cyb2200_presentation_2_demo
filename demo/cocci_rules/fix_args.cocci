// Rule: fix_args.cocci
// PATCH mode - Updates foo() calls from 3 args to 2 args
//
// Run (dry):   spatch --sp-file cocci_rules/fix_args.cocci c_files/vulnerable.c
// Run (apply): spatch --sp-file cocci_rules/fix_args.cocci --in-place c_files/vulnerable.c


@@
expression arg1, arg2, arg3;
@@

- foo(arg1, arg2, arg3);
+ foo(arg1, arg2);
