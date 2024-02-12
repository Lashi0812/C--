#include <functional>
#include <iostream>
#include <string>
#include <thread>

void greet(std::string const &greet) { std::cout << greet << " World!" << std::endl; }

void f() {
    std::thread t(greet, "Hello");
    t.join();
}

void add5(int &v) { v += 5; }

void f1() {
    int         a = 10;
    std::thread t1(add5, std::ref(a)); // pass the ref
    t1.join();

    std::cout << "Value in a : " << a << std::endl;
}

class Greet {
  public:
    void greet_world(std::string const &greet) { std::cout << greet << " World!" << std::endl; }
};

void f3() {
    Greet       obj;
    std::thread t(&Greet::greet_world, &obj, "Hello"); // obj.greet_world("hello")
    t.join();
}

int main() {
    f();
    f1();
    f3();
}