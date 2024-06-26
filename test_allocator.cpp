#include <gtest/gtest.h>
#include <string>
#include "my_vector.h"
#include "factorial.h"

template <typename T>
std::string container_string(serial_container<T> &arr) {
    std::string str = "";
    for (size_t i = 0; i < arr.size(); i++) {
        str += std::to_string(arr[i]) + ' ';
    }
    return str;
}

TEST(VectorTest, array_container) {
    serial_container<int> arr;

    for (size_t i = 0; i < 10; i++) {
        arr.push_back(i);
    }

    std::string values = container_string(arr);
    EXPECT_EQ(values, "0 1 2 3 4 5 6 7 8 9 ");
}

TEST(VectorTest, array_pushback) {
    serial_container<int> arr;

    for (size_t i = 0; i < 10; i++) {
        arr.push_back(i);
    }
    arr.push_back(42);
    std::string values = container_string(arr);
    EXPECT_EQ(values, "0 1 2 3 4 5 6 7 8 9 42 ");

    arr.push_back(718);
    std::string values_t = container_string(arr);
    EXPECT_EQ(values_t, "0 1 2 3 4 5 6 7 8 9 42 718 ");
}

TEST(VectorTest, array_erase) {
    serial_container<int> arr;

    for (size_t i = 0; i < 10; i++) {
        arr.push_back(i);
    }
    arr.erase(1);
    std::string values = container_string(arr);
    EXPECT_EQ(values, "0 2 3 4 5 6 7 8 9 ");

    arr.erase(8);
    std::string values_t = container_string(arr);
    EXPECT_EQ(values_t, "0 2 3 4 5 6 7 8 ");
}

TEST(VectorTest, array_insert) {
    serial_container<int> arr;

    for (size_t i = 0; i < 10; i++) {
        arr.push_back(i);
    }
    arr.insert(3, 42);
    std::string values = container_string(arr);
    EXPECT_EQ(values, "0 1 2 42 3 4 5 6 7 8 9 ");

    arr.insert(0, 718);
    std::string values_t = container_string(arr);
    EXPECT_EQ(values_t, "718 0 1 2 42 3 4 5 6 7 8 9 ");
}

TEST(VectorTest, array_size) {
    serial_container<int> arr;

    for (size_t i = 0; i < 10; i++) {
        arr.push_back(i);
    }
    EXPECT_EQ(arr.size(), 10);

    arr.erase(2);
    EXPECT_EQ(arr.size(), 9);

    arr.erase(0);
    EXPECT_EQ(arr.size(), 8);

    arr.push_back(42);
    EXPECT_EQ(arr.size(), 9);

    arr.insert(1, 718);
    EXPECT_EQ(arr.size(), 10);
}

TEST (Factorial,factorial_test){
    EXPECT_EQ(factorial(0), 1);
    EXPECT_EQ(factorial(1), 1);
    EXPECT_EQ(factorial(5), 120);
    EXPECT_EQ(factorial(11), 39916800);
}