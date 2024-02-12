#include <iostream>
#include <mutex>

class Counter {
  public:
    Counter() : count(0){};
    void increment() {
        std::lock_guard<std::mutex> guard(mutex);
        count++;
    }

    int *getCount() {
        std::lock_guard<std::mutex> guard(mutex);
        return &count;
    }

  private:
    int        count;
    std::mutex mutex;
};

int main() {
    Counter counter;
    counter.increment();
    counter.increment();
    std::cout << "Current count : " << *counter.getCount() << std::endl;
    int *protect_data = counter.getCount();
    *protect_data     = 100;
    counter.increment();
    counter.increment();
    std::cout << "Current count : " << *counter.getCount() << std::endl;
}