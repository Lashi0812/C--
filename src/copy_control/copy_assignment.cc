#include <iostream>

class Foo {
  public:
    Foo() = default;
    Foo(int magicNumber) : magicNumber(magicNumber){};
    Foo &operator=(const Foo &other) {
        std::cout << "📢 Calling the Copy Assignment  " << std::endl;
        this->magicNumber = other.magicNumber;
        return *this;
    }
    int getMagicNumber() { return magicNumber; }

  private:
    int magicNumber;
};

int main() {
    Foo A(42), B;
    B = A;
    std::cout << "B has magic number : " << B.getMagicNumber() << std::endl;
    return 0;
}