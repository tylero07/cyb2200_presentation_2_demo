# Coccinelle Demo — CYB2200 Security Vulnerabilities
## Complete demo package for detecting and patching C vulnerabilities

---

## Setup

```bash
# Install Coccinelle
sudo apt install coccinelle    # Ubuntu/Debian
brew install coccinelle        # macOS

# Verify
spatch --version

# Navigate to the demo directory
cd coccinelle_demo
```

---

## File Layout

```
demo/
├── c_files/
│   ├── vulnerable.c     ← starting point: 5 vulnerabilities
│   └── fixed.c          ← reference: what fully patched code looks like
├── cocci_rules/
│   ├── detect_gets.cocci           ← find gets() calls
│   ├── fix_gets.cocci              ← gets()  → fgets()
│   ├── detect_strcpy.cocci         ← find strcpy() calls
│   ├── fix_strcpy.cocci            ← strcpy() → strncpy()
│   ├── detect_format_string.cocci  ← find printf(var) calls
│   ├── fix_format_string.cocci     ← printf(E) → printf("%s", E)
│   ├── detect_sprintf.cocci        ← find sprintf() calls
│   └── detect_malloc_no_check.cocci← find malloc() without NULL check
└── README.md
```

---

## Demo Script (step by step)

### Step 1 — Look at the vulnerable code
```bash
cat c_files/vulnerable.c
```
Point out the 5 vulnerability sites to your audience.

---

### Step 2 — Detect gets()
```bash
spatch --sp-file cocci_rules/detect_gets.cocci c_files/vulnerable.c
```
Coccinelle prints lines marked with `*` — those are the dangerous sites.

---

### Step 3 — Patch gets() → fgets() (dry run first)
```bash
# Dry run: show the diff without touching the file
spatch --sp-file cocci_rules/fix_gets.cocci c_files/vulnerable.c

# Apply it
cp c_files/vulnerable.c c_files/patching.c
spatch --sp-file cocci_rules/fix_gets.cocci --in-place c_files/patching.c
```

---

### Step 4 — Detect strcpy()
```bash
spatch --sp-file cocci_rules/detect_strcpy.cocci c_files/vulnerable.c
```

---

### Step 5 — Detect the format string bug
```bash
spatch --sp-file cocci_rules/detect_format_string.cocci c_files/vulnerable.c
```
Explain: `printf(user_input)` lets an attacker inject `%x`, `%s`, `%n` to read
or write memory. The fix is `printf("%s", user_input)`.

---

### Step 6 — Detect sprintf()
```bash
spatch --sp-file cocci_rules/detect_sprintf.cocci c_files/vulnerable.c
```
Explain that `snprintf()` is the safe alternative — it takes a size parameter.

---

### Step 7 — Detect malloc without NULL check
```bash
spatch --sp-file cocci_rules/detect_malloc_no_check.cocci c_files/vulnerable.c
```

---

### Step 8 — Run ALL detections at once on a whole directory
```bash
for rule in cocci_rules/detect_*.cocci; do
    echo "=== $rule ==="
    spatch --sp-file "$rule" c_files/vulnerable.c
done
```

---

### Step 9 — Compare vulnerable vs fixed
```bash
diff c_files/vulnerable.c c_files/fixed.c
```

---

## Key spatch Flags

| Flag | What it does |
|------|-------------|
| `--sp-file foo.cocci` | Specify the semantic patch file |
| `--in-place` | Modify the C file directly (no backup) |
| `--dir ./src` | Run against a whole directory of C files |
| `-U 3` | Show 3 lines of context around matches |
| `--include-headers` | Also check #included header files |
| `--very-quiet` | Suppress verbose output, only show matches |

---

## SmPL (Semantic Patch Language) Quick Reference

```cocci
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
```

---

## Vulnerability Map (links to your lectures)

| Vulnerability | Unsafe Function | Safe Alternative | Lecture |
|---------------|----------------|-----------------|---------|
| Buffer overflow (stack) | `gets()` | `fgets(buf, n, stdin)` | L5 |
| Buffer overflow (string copy) | `strcpy()` | `strncpy(dst, src, n)` | L3, L4 |
| Buffer overflow (format write) | `sprintf()` | `snprintf(buf, n, fmt, ...)` | L3 |
| Format string attack | `printf(var)` | `printf("%s", var)` | L7, L8 |
| Heap / NULL deref | `malloc()` no check | Check `if (ptr == NULL)` | L6 |

---

## Notes

- Coccinelle matches **semantically**, not textually — it understands C syntax.
- It works well across a whole codebase: `--dir ./src` recursively finds all `.c` files.
- The Linux kernel uses Coccinelle extensively for safe large-scale refactoring.
- It does NOT replace a compiler's `-Wall` warnings but complements them.
