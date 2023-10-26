#include <cstdio>
#include <iostream>
#include <string>

void hello() {
    char hello[] = "Hello World!\n";
    std::cout << hello;
}

void while_count(int n) {
    int count = 0;
    while (count < n) {
        std::cout << count;
        count++;
    }
    std::cout << std::endl;
}

void for_count(int n) {
    for (int i = 0; i < n; i++) {
        std::cout << i;
    }
    std::cout << std::endl;
}

void pointer_madness() {
    char *msg = "OhMyGodNoWayyy";
    printf("%c\n", *(msg + 7));
    printf("%c\n", msg[7]);

    int x = 4;
    int *z = &x;
    int **y = &z; // There's no limit for *'s
    printf("Address: %p, Value: %d\n", &x, x);
    printf("Address: %p, Value: %p, Inner value: %d\n", &z, z, *z);
    printf("Address: %p, Value: %p, Inner value: %p, Inner inner value: %d\n",
           &y, y, *y, **y);

    **y = 16;
    printf("%d\n", x);
}

class Person {
  public:
    std::string name;
    Person(std::string _name) { name = _name; }
};

int main() {
    hello();
    while_count(100);
    for_count(100);
    pointer_madness();

    Person p("Luis");

    std::cout << p.name << std::endl;

    std::string input;
    std::cin >> input;
    std::cout << "Your input: " << input << std::endl;

    return 0;
}
