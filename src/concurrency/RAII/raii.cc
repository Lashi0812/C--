#include <thread>

class thread_guard {
  public:
    explicit thread_guard(std::thread &_t) : t(_t) {}
    ~thread_guard() {
        if (t.joinable()) {
            t.join();
        }
    }

    thread_guard(const thread_guard &)            = delete;
    thread_guard &operator=(const thread_guard &) = delete;

  private:
    std::thread &t;
};

void do_something(int &i) { ++i; }

struct func {
    int &i;

    func(int &i_) : i(i_) {}

    void operator()() {
        for (unsigned j = 0; j < 1000000; ++j) {
            do_something(i);
        }
    }
};

void do_something_in_current_thread() {}

void f() {
    int          some_local_state;
    func         my_func(some_local_state);
    std::thread  t(my_func);
    thread_guard g(t);

    do_something_in_current_thread();
}

int main() { f(); }
