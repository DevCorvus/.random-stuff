#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define DAYS_IN_YEAR 365

int add(int n1, int n2);
int substract(int n1, int n2);
float average(int arr[], size_t size);
void swap_two_numbers(int *a, int *b);

static int v = 4; // Only accessible within this file
typedef char *string;

enum days { MON, TUE, WED, THU, FRI = 69, SAT, SUN };

// struct rectangle
// {
//     int width;
//     int height;
// };
// typedef struct rectangle rect;

typedef struct {
    int width;
    int height;
} rect;

/*
   "%d";    // integer
   "%3d";   // integer with minimum of length 3 digits (right justifies text)
   "%s";    // string
   "%f";    // float
   "%ld";   // long
   "%3.2f"; // minimum 3 digits left and 2 digits right decimal float
   "%7.4s"; // (can do with strings too)
   "%c";    // char
   "%p";    // pointer. NOTE: need to (void *)-cast the pointer, before passing
            //                it as an argument to `printf`.
            "%x";    // hexadecimal
            "%o";    // octal
            "%%";    // prints %
            */

// int main(void)
int main(int argc, char *argv[]) {
    extern int v; // Accessing external variable

    // struct rectangle my_rect = {1, 2};
    // my_rect.width = 40;
    // my_rect.height = 60;
    rect my_rect = {4, 3};
    my_rect.width = 40;
    my_rect.height = 60;

    if (argc > 1) {
        // The first argument is literally the command for executing the file
        // (its name, in this case ./hello)
        printf("%s\n", argv[1]);
    }

    printf("Hello, world in C\n");
    printf("The result for adding 2 + 2 is: %d\n", add(2, 2));
    printf("The result for substracting 2 - 2 is: %d\n", substract(2, 2));

    char ch = 'L'; // 1 Byte (Represents its ASCII code)
    int chi = 'L'; // ASCII code directly

    short ns = 4;           // 2 Bytes
    int ni = 32;            // 4 Bytes
    long nl = 10;           // 8 Bytes (maybe)
    long long nll = 20;     // 8 Bytes (secured)
    float nf = 0.0f;        // 4 Bytes
    double nd = 0.0;        // 8 Bytes
    unsigned short nus = 4; // 2 Bytes (No negatives)
                            // There are unsigned variations for others as well

    // You have to import a library in order to use booleans
    bool illo = true;

    int hex = 0x01;
    int *np;
    np = &ni;

    // Multiple variable declarations
    int k = 20, l = 40;

    char ternary = 4 > 2 ? 'S' : 'F';

    switch (ternary) {
    case 'S':
        printf("Sublime");
        break;

    case 'F':
        printf("Just F");
        break;

    default:
        break;
    }

    char text[20]; // ? Bytes, STRING (array of characters). It contains 1 Byte
                   // of Char * 20

    printf("Enter some text: ");
    scanf("%s", text);

    printf("Your input is: %s\n", text);

    int age;

    printf("Enter your age: ");
    scanf("%i", &age);

    if (age >= 18) {
        printf("You can pass\n");
    } else {
        printf("You cannot pass\n");
    }

    int i = 0;
    while (i < 3) {
        printf("REPEAT\n");
        // i = i + 1;
        // i += 1;
        i++;
    }

    for (int i = 0; i < 3; i++) {
        printf("REPEAT (for loop)\n");
    }

    // This is not the best use for a do-while loop
    int c;
    do {
        printf("REPEAT (do while)\n");
        c++;
    } while (c < 3);

    int scores_size = 3;

    int scores[scores_size];
    // scores[0] = 50;
    // scores[1] = 90;
    // scores[2] = 70;

    for (int i = 0; i < scores_size; i++) {
        printf("Enter your score #%i: ", i + 1);
        scanf("%i", &scores[i]);
    }

    // printf("Your average is: %f\n", (50 + 90 + 70) / 3.0);
    // printf("Your average is: %f\n", (scores[0] + scores[1] + scores[2]) /
    // (float)3);
    printf("Your average is: %f\n", average(scores, scores_size));

    int arr[] = {3, 5, 9};
    int arr_len1 = *(&arr + 1) - arr; // using pointer arithmetic
    int arr_len2 =
        sizeof(arr) /
        sizeof(
            int); // sizeof() returns the bytes length of the datatype
                  // It is not possible to get the size of an array dinamically
                  // in C, just this way (knowing its size) But you can do with
                  // strings because they have that "tail" NUL (\0)

    printf("The length of the int array is: %d/%d\n", arr_len1, arr_len2);

    // String literal (non-mutable)
    const char *name = "Luis";
    // The compiler can infer the size automatically
    // char message[4] = {'H', 'i', '!', '\0'};
    char message[] = {'H', 'i', '!', '\0'}; // You must include the tail

    // Printing ASCII values corresponding to the characters including the tail
    // which is NUL (\0)
    printf("%i %i %i %i %i\n", name[0], name[1], name[2], name[3], name[4]);
    // Printing pointer reference
    printf("%p\n", name);

    char words[2][4] = {"uwu", "awa"};

    printf("%c%c%c\n", words[0][0], words[0][1], words[0][2]);
    printf("%c%c%c\n", words[1][0], words[1][1], words[1][2]);

    // Lenght of string
    // int len = 0;
    // while (name[len] != '\0')
    // {
    //     len++;
    // }
    // printf("Lengh of name: %i\n", len);
    printf("Lengh of name: %li\n", strlen(name));

    char upper_name[4];
    for (int i = 0; i < strlen(name); i++) {
        if (name[i] >= 'a' && name[i] <= 'z') {
            // name[i] -= 32;
            upper_name[i] =
                name[i] -
                32; // By substracting 32, we are shifting from the lowercase to
                    // uppercase character corresponded in the ASCII table
        } else {
            upper_name[i] = name[i];
        }
    }
    printf("Name in uppercase: %s\n", name);

    if (islower(name[2])) {
        printf("%c\n", toupper(name[2])); // If it is already uppercase, it'll
                                          // just return it as it is
    }

    char ciphertext[4];
    for (int i = 0; i < strlen(name); i++) {
        ciphertext[i] = name[i] + 1;
    }
    printf("Ciphertext: %s\n", ciphertext);

    char plaintext[4];
    for (int i = 0; i < strlen(name); i++) {
        plaintext[i] = ciphertext[i] - 1;
    }
    printf("Plaintext: %s\n", plaintext);

    // Exit status visible with "echo $?" (useful to indicate error codes)
    // return 0; // This is returned by default
    // return 1;
}

int add(int n1, int n2) { return n1 + n2; }

int substract(int n1, int n2) { return n1 - n2; }

float average(int arr[], size_t size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return (sum / (float)size);
}

void swap_two_numbers(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
