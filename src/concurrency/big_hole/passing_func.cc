#include <iostream>
#include <mutex>

class Counter {
  public:
    Counter() : count(0){};
    void increment() {
        std::lock_guard<std::mutex> guard(mutex);
        count++;
    }

    int getCount() {
        std::lock_guard<std::mutex> guard(mutex);
        return count;
    }

    template <typename Function>
    void process_count(Function func) {
        std::lock_guard<std::mutex> guard(mutex);
        int dummy = count;
        func(dummy);
    }

  private:
    int        count;
    std::mutex mutex;
};

int *protect_data;
void malicious_func(int &data) { protect_data = &data; }


int  main() {
    Counter counter;
    counter.increment();
    counter.increment();
    std::cout << "Current count : " << counter.getCount() << std::endl;

    counter.process_count(malicious_func);
    *protect_data = 100;

    counter.increment();
    counter.increment();
    std::cout << "Current count : " << counter.getCount() << std::endl;
}