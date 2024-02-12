#include <iostream>
#include <thread>
#include <vector>

void do_something(int i) { std::cout << "doing work for " << i << std::endl; }
void f() {
    std::vector<std::thread> threads;
    for (int i{0}; i < 20; ++i) {
        threads.emplace_back(do_something, i);
    }

    for (auto &entry : threads) {
        entry.join();
    }
}

int main() { f(); }