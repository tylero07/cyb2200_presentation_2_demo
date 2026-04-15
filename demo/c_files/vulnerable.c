#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* -------------------------------------------------------
 * VULNERABILITY 1: gets() — unbounded input, no size check
 * ------------------------------------------------------- */
void read_username() {
    char buf[64];
    gets(buf);   /* UNSAFE: no bounds checking whatsoever */
    printf("Hello, %s\n", buf);
}

/* -------------------------------------------------------
 * VULNERABILITY 2: strcpy() — unbounded copy
 * ------------------------------------------------------- */
void copy_input(char *user_input) {
    char dest[32];
    strcpy(dest, user_input);   /* UNSAFE: src may be longer than dest */
    printf("Copied: %s\n", dest);
}

/* -------------------------------------------------------
 * VULNERABILITY 3: sprintf() — unbounded format write
 * ------------------------------------------------------- */
void build_message(char *name, int code) {
    char msg[32];
    sprintf(msg, "User %s has code %d", name, code);   /* UNSAFE: no size limit */
    puts(msg);
}

/* -------------------------------------------------------
 * VULNERABILITY 4: printf(user_input) — format string vulnerability
 * ------------------------------------------------------- */
void log_event(char *user_input) {
    printf(user_input);   /* UNSAFE: user controls format string */
}


int main(int argc, char *argv[]) {
    read_username();
    if (argc > 1) {
        copy_input(argv[1]);
        log_event(argv[1]);
    }
    build_message("Alice", 42);
    return 0;
}
