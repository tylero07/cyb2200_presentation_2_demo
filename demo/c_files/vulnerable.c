#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* -------------------------------------------------------
 * VULNERABILITY 1: gets() — unbounded input, no size check
 * ------------------------------------------------------- */
void example1() {
    char buf[64];
    gets(buf);  
    printf("Hello, %s\n", buf);
}

/* -------------------------------------------------------
 * VULNERABILITY 2: strcpy() — unbounded copy
 * ------------------------------------------------------- */
void example2(char *user_input) {
    char dest[32];
    strcpy(dest, user_input);   
    printf("Copied: %s\n", dest);
}

/* -------------------------------------------------------
 * VULNERABILITY 3: sprintf() — unbounded format write
 * ------------------------------------------------------- */
void example3(char *name, int code) {
    char msg[32];
    sprintf(msg, "User %s has code %d", name, code);   
    puts(msg);
}

/* -------------------------------------------------------
 * VULNERABILITY 4: printf(user_input) — format string vulnerability
 * ------------------------------------------------------- */
void example4(char *user_input) {
    printf(user_input);  
}

/* -------------------------------------------------------
 * VULNERABILITY 5: malloc() — return value never checked for NULL
 * ------------------------------------------------------- */
void example5(int n) {
    int *arr;
    arr = malloc(sizeof(int) * n); 
    *arr = 42;                       
    printf("arr[0] = %d\n", *arr);
    free(arr);
}

/* -------------------------------------------------------
 * REFACTOR: 3 args to 2.
 * ------------------------------------------------------- */
void foo(int a, int b, int c) {
    printf("a=%d b=%d c=%d\n", a, b, c); 
}
// void foo(int a, int b) {
//     printf("a=%d b=%d\n", a, b); 
// }


int main(int argc, char *argv[]) {
    foo(1, 2, 3); 
    return 0;
}
