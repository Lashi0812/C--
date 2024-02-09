#include <iostream>
#include <vector>

class Foo {
  public:
    Foo() = default;
    Foo(int num) : magic_number(num) {}
    Foo(const Foo &other) : magic_number(other.magic_number) {
        std::cout << "Calling Copy Constructor" << std::endl;
    }
    int getMagicNumber() { return magic_number; }

  private:
    int magic_number = 0;
};

Foo global;
Foo passingFooAndReturnFoo(Foo other) {
    std::cout << "Local Copy : ";
    Foo local = other;
    std::cout << "Creating Foo Pointer : ";
    Foo *heap = new Foo(global);
    std::cout << "Assigning Foo to Foo Pointer : \n";
    *heap = local;
    std::cout << "Creating the Foo Array : ";
    Foo fooArray[4] = {local, *heap};
    std::cout << "Returning the Foo : ";
    return *heap;
}

class AggregateClass {
  public:
    Foo  some;
    void get(){};
};

int main() {
    Foo A = Foo(42'000);
    std::cout << "Assessing the Foo : ";
    Foo B = A;
    std::cout << "Passing the Foo : ";
    passingFooAndReturnFoo(B);
    std::cout << "Using Foo in Brace initialization of Agg Class: ";
    AggregateClass agg = {B};
    std::cout << "Using Foo in Brace initialization of Vector : ";

    std::vector<Foo> fooVector;
    fooVector.push_back(A);
}