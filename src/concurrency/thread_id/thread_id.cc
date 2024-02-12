#include <iostream>
#include <thread>
#include <vector>

void print_thread_id(){
    std::cout << std::this_thread::get_id() << std::endl;
}

int main(){
    std::vector<std::thread> threads;
    for (int i{0}; i < 5; ++i) {
        threads.emplace_back(print_thread_id);
    }

    for(auto& entry : threads){
        entry.join();
    }
}