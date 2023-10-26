#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *text1 = "hello!";

    // Every time you use malloc or equivalents... free the memory.
    char *text2 = malloc(strlen(text1) + 1);
    if (text2 == NULL) {
        return 1;
    }

    for (int i = 0, len = strlen(text1) + 1; i < len; i++) {
        *(text2 + i) = *(text1 + i);
    }

    if (strlen(text2) > 0) {
        text2[0] = 'H';
    }

    printf("Text #1: %s\n", text1);
    printf("Text #2: %s\n", text2);

    // ALWAYS FREE THE MEMORY THAT YOU MANUALLY REQUIRED
    free(text2);

    return 0;
}
