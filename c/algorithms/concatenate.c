#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int len(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

void append(char *dest, char *src) {
    char *c = src;

    int i = len(dest);
    while (*c != '\0') {
        dest[i++] = *c;
        c++;
    }
    dest[i] = '\0';
}

// Allocating this way is not that idiomatic
char *concat(char *s1, char *s2) {
    int capacity = (len(s1) + len(s2)) + 1;
    char *out = malloc(sizeof(char) * capacity);

    append(out, s1);
    append(out, s2);

    return out;
}

int main(void) {
    char *str1 = "Hello ";
    char *str2 = "World";

    char *msg = concat(str1, str2);
    printf("%s\n", msg);
    free(msg);

    return 0;
}
