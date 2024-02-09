/*
When the Destructor is Called
1. Variable out of scope
2. Member of object is destroyed
    a. B contain A when B is deleted , A destructor is called
3. Container is deleted.
*4. Temporary object is deleted
*/

#include <iostream>
#include <vector>
class MyInt {
  public:
    MyInt() = default;
    MyInt(int value) : value(value) {}
    MyInt operator+(const MyInt &rhs) { return MyInt(value + rhs.value); }
    ~MyInt() { std::cout << "Calling the Destructor for value " << value << std::endl; }

    int getValue() { return value; }

  private:
    int value = 100;
};

class IntTenContainer {

  private:
    MyInt ten{10};
};

int main() {
    // ? Out of scope
    {
        MyInt out(13);
        std::cout << "Going out of scope : ";
    }
    // ? member of other type
    IntTenContainer container;

    // ? element in container
    std::vector<MyInt> elemContainer;
    elemContainer.push_back(MyInt{101});

    //? Using delete for dynamically allocate object
    MyInt *test = new MyInt[2];
    test[0]     = MyInt{200};
    test[1]     = MyInt{201};
    delete[] test;

    // ? Temporary object
    std::cout << "Using temporary MyInt object: " << MyInt(42).getValue() << std::endl;
    std::cout << "Program going to End" << std::endl;
    return 0;
}