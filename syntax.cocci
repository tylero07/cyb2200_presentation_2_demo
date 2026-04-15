@@                  ← metavariable block (required, even if empty)
expression E;       ← matches any expression
type T;             ← matches any type
T *ptr;             ← typed metavariable (pointer to T)
expression list L;  ← matches a comma-separated argument list
statement S;        ← matches any single statement
@@

* foo(E);           ← * means "flag this line" (detect mode)
- old_call(E);      ← - means "remove this line"
+ new_call(E, n);   ← + means "add this line"
  context_line;     ← no prefix = anchor/context (must match but not changed)