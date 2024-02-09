/*
Destructor is not called when the reference goes out scope
*/

#include <iostream>
class MyInt {
  public:
    MyInt() = default;
    MyInt(int value) : value(value){};
    ~MyInt() { std::cout << "Calling the Destructor for value " << value << std::endl; }
    int getValue() { return value; }

  private:
    int value;
};

int main() {
    {
        MyInt  two{2};
        MyInt *ptr = new MyInt(3);
        std::cout << ptr->getValue() << std::endl;
        std::cout << "Going out of scope: ";

        /*
        bazel run --run_under="valgrind --leak-check=full -s" //src/copy_control:dest_pit_fall_ref
        ! run with valgrind you see the memory leak since dynamic memory not delete
        * uncomment and again check with valgrind there will no memory leak
         */
        // delete ptr;
    }
    std::cout << "Program going to End : " << std::endl;
}