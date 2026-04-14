// Rule: detect_malloc_no_check.cocci
// DETECT mode — finds malloc() calls not immediately followed by a NULL check
// Dereferencing a NULL pointer from malloc is undefined behavior / crash
// Covered in: CYB2200 L6 Heap Buffer Overflow
//
// This rule uses a "disjunction + negation" pattern:
//   match malloc assignment where the next statement is NOT an if(...NULL...)
//
// Run: spatch --sp-file detect_malloc_no_check.cocci vulnerable.c

@@
type T;
T *ptr;
expression size;
statement S;
@@

  ptr = (T *) malloc(size);
(
  if (ptr == NULL) S
|
* ptr = (T *) malloc(size);
)
