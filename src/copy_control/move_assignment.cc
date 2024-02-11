/*
Move Assignment that the rvalue reference as the 1st parameter
1. Check for self Assignment
2. Free the lhs
3. take over the member variable of rhs
*4. set the rhs member variable to nullptr to prevent double deletion
*/

#include <algorithm>
#include <iostream>
#include <string>

class MyClass {
  public:
    MyClass() = default;
    MyClass(const std::string &str) : str(new std::string(str)) {}
    MyClass(const MyClass &other) = delete;

    MyClass(MyClass &&other) noexcept { std::swap(str, other.str); }

    MyClass &operator=(MyClass &&rhs) noexcept {
        // check for self assignment
        if (this != &rhs) {
            delete str;        // free lhs
            str     = rhs.str; // take over the rhs
            rhs.str = nullptr; // set the rhs to null for prevent double deletion
        }
        return *this;
    }
    ~MyClass() { delete str; }

    void display() const { std::cout << "Data: " << (str ? *str : "") << std::endl; }

  private:
    std::string *str;
};

int main() {
    MyClass obj1("Lakshman");
    MyClass obj2("LAshi");

    std::cout << "Before move:" << std::endl;
    obj1.display();
    obj2.display();

    // Move assignment
    obj1 = std::move(obj2);

    std::cout << "After move:" << std::endl;
    obj1.display();
    obj2.display();
}