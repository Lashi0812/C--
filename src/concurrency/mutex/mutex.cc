#include <algorithm>
#include <iostream>
#include <list>
#include <mutex>


std::list<int> some_list;
std::mutex     some_mutex;

void add_to_list(int value) {
    std::lock_guard<std::mutex> guard(some_mutex);
    some_list.push_back(value);
}

bool list_contains(int value) {
    std::lock_guard<std::mutex> guard(some_mutex);
    return std::find(some_list.begin(), some_list.end(), value) != some_list.end();
}

int main() {
    add_to_list(42);
    std::cout << "contains(1) = " << list_contains(1) << "\ncontains(42) = " << list_contains(42)
              << std::endl;
}