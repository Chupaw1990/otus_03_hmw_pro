#include <iostream>
#include <map>

#include "my_allocator.h"
#include "my_vector.h"
#include "factorial.h"



int main() {
    std::map<int, int> map_test;
    for (size_t i = 0; i < 10; i++) {
        int value = factorial(i);
        map_test.emplace(std::make_pair(i, value));
    }

    std::cout << "std::map with defaut allocator:" << std::endl;

    for (const auto& i : map_test) {
        std::cout << i.first << " " << i.second << std::endl;
    }

    std::map<int, int, std::less<>,
             custom_allocator<std::pair<const int, int>, 10>>
        map_custom_alloc;

    for (size_t i = 0; i < 10; i++) {
        int value = factorial(i);
        map_test.emplace(std::make_pair(i, value));
    }

    std::cout << "std::map with custom allocator:" << std::endl;

    for (const auto& i : map_test) {
        std::cout << i.first << " " << i.second << std::endl;
    }

    serial_container<int> vector_test;

    for (size_t i = 0; i < 10; i++) {
        vector_test.push_back(i);
    }

    std::cout << "custom container with defaut allocator:" << std::endl;

    for (const auto& i : vector_test) {
        std::cout << i << std::endl;
    }

    serial_container<int, custom_allocator<int, 10>> vector_test_allocator;

    for (size_t i = 0; i < 10; i++) {
        vector_test_allocator.push_back(i);
    }

    std::cout << "custom container with custom allocator:" << std::endl;

    for (const auto& i : vector_test_allocator) {
        std::cout << i << std::endl;
    }

    return 0;
}