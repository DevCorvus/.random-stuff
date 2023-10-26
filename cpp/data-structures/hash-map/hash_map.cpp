#include "hash_map.h"
#include <iostream>
#include <string>

int main(void) {
    HashMap<int, std::string> hmap;
    hmap.put(1, "uwu");
    hmap.put(2, "awa");
    hmap.put(3, "ewe");
    hmap.put(4, "owo");

    hmap.put(1, "UwU");

    std::string value = hmap.get(1);

    std::cout << value << std::endl;
}
