#include <stdio.h>

void old_log(const char *credentials) {
    printf("OLD LOG: %s\n", credentials);
}

void new_log(const char *credentials) {
    printf("NEW LOG: [REDACTED/SECURE] %s\n", credentials);
}

int main(void) {
    old_log("user:admin password:1234");
    old_log("token=abcd1234");
    old_log("apikey=secretkey");
    return 0;
}