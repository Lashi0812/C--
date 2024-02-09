/*
Default Copy Constructor do Shallow copy
*/

#include <iostream>
class DefaultCopyConstructor {
  public:
    DefaultCopyConstructor(int size) : data(new int[size]), size(size) {
        for (int i{0}; i < size; ++i) {
            data[i] = i;
        }
    }

    //! this will throw error for trying to delete which already deleted
    // ~DefaultCopyConstructor() { delete[] data; }

    void printData() {
        for (int i{0}; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    void changeValue(int index, int value) { data[index] = value; }

  private:
    int *data;
    int  size;
};

int main() {
    DefaultCopyConstructor obj1(5), obj2(5);
    obj1 = obj2;
    std::cout << "Data at obj1 before change : ";
    obj1.printData();
    std::cout << "Data at obj2 before change : ";
    obj2.printData();
    obj2.changeValue(2, 100);
    std::cout << "Data at obj1 after change : ";
    obj1.printData();
    std::cout << "Data at obj2 after change : ";
    obj2.printData();
    return 0;
}