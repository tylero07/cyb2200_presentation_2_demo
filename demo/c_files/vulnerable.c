/* vulnerable.c
 * Demo file for Coccinelle static analysis
 * Contains: buffer overflow, format string, gets(), unsafe strcpy/sprintf
 * Mirrors examples from CYB2200 lectures
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* -------------------------------------------------------
 * VULNERABILITY 1: gets() — unbounded input, no size check
 * (From L5 buffer overflow lecture)
 * ------------------------------------------------------- */
void read_username() {
    char buf[64];
    gets(buf);   /* UNSAFE: no bounds checking whatsoever */
    printf("Hello, %s\n", buf);
}

/* -------------------------------------------------------
 * VULNERABILITY 2: strcpy() — unbounded copy
 * (From L3/L4 C strings lecture)
 * ------------------------------------------------------- */
void copy_input(char *user_input) {
    char dest[32];
    strcpy(dest, user_input);   /* UNSAFE: src may be longer than dest */
    printf("Copied: %s\n", dest);
}

/* -------------------------------------------------------
 * VULNERABILITY 3: sprintf() — unbounded format write
 * (From L3 unbounded string functions)
 * ------------------------------------------------------- */
void build_message(char *name, int code) {
    char msg[32];
    sprintf(msg, "User %s has code %d", name, code);   /* UNSAFE: no size limit */
    puts(msg);
}

/* -------------------------------------------------------
 * VULNERABILITY 4: printf(user_input) — format string bug
 * (From L7/L8 metacharacter / format string lecture)
 * ------------------------------------------------------- */
void log_event(char *user_input) {
    printf(user_input);   /* UNSAFE: user controls format string */
}

/* -------------------------------------------------------
 * VULNERABILITY 5: malloc with no NULL check
 * (From L6 heap buffer overflow lecture)
 * ------------------------------------------------------- */
void allocate_buffer(int size) {
    char *buf = malloc(size);
    /* UNSAFE: no check if malloc returned NULL */
    strcpy(buf, "hello");
    free(buf);
}

int main(int argc, char *argv[]) {
    read_username();
    if (argc > 1) {
        copy_input(argv[1]);
        log_event(argv[1]);
    }
    build_message("Alice", 42);
    allocate_buffer(16);
    return 0;
}
