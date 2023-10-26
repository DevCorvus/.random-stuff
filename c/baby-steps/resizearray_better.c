#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *list = malloc(3 * sizeof(int));
    if (list == NULL) {
        return 1;
    }

    // *list = 1;
    // *(list+1) = 2;
    // *(list+2) = 3;
    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    // ...

    for (int i = 0; i < 3; i++) {
        printf("%i\n", list[i]);
    }

    // This will automate the copy and freeing process and tmp in this case is
    // only used to check if there's no problem If you reasign the value of list
    // and there's a problem with realloc, that would produce a memory leak And
    // it is even more efficient by smartly "expanding" the original chunk of
    // memory if possible
    int *tmp = realloc(list, 4 * sizeof(int));
    if (tmp == NULL) {
        free(list);
        return 1;
    }
    list = tmp;

    list[3] = 4;

    for (int i = 0; i < 4; i++) {
        printf("%i\n", list[i]);
    }

    // I'm done with list so at the end...
    free(list);

    return 0;
}
