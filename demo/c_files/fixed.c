/* fixed.c
 * Patched version of vulnerable.c
 * Shows what Coccinelle transforms the code INTO
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* FIX 1: fgets() replaces gets() — bounded input */
void read_username() {
    char buf[64];
    fgets(buf, sizeof(buf), stdin);   /* SAFE: size bounded */
    printf("Hello, %s\n", buf);
}

/* FIX 2: strncpy() replaces strcpy() — bounded copy */
void copy_input(char *user_input) {
    char dest[32];
    strncpy(dest, user_input, sizeof(dest) - 1);   /* SAFE: n limits copy length */
    dest[sizeof(dest) - 1] = '\0';                 /* ensure NUL termination */
    printf("Copied: %s\n", dest);
}

/* FIX 3: snprintf() replaces sprintf() — bounded format write */
void build_message(char *name, int code) {
    char msg[32];
    snprintf(msg, sizeof(msg), "User %s has code %d", name, code);   /* SAFE */
    puts(msg);
}

/* FIX 4: explicit format string in printf */
void log_event(char *user_input) {
    printf("%s", user_input);   /* SAFE: format string is a literal */
}

/* FIX 5: malloc with NULL check */
void allocate_buffer(int size) {
    char *buf = malloc(size);
    if (buf == NULL) {          /* SAFE: check before use */
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    strncpy(buf, "hello", size - 1);
    buf[size - 1] = '\0';
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
