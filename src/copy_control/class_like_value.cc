/*
Classes are behave like value ie they have the own state
1. Copy Constructor own the object by creating the deep copy
2. Destructor should free dynamically allocated object.
3. Copy Assignment
    a. check for self assignment
    b. Free the existing object
    c. copy the object from the rhs.
*/

#include <iostream>
#include <string>
class HumanValueLike {
  public:
    HumanValueLike(const std::string name, int age) : age(age), name(new std::string(name)) {}
    HumanValueLike(const HumanValueLike &other)
        : age(other.age), name(new std::string(*other.name)) {
        std::cout << "Calling the Copy Constructor \n";
    }
    ~HumanValueLike() { delete name; }
    HumanValueLike &operator=(const HumanValueLike &rhs);
    void            print() {
        std::cout << "name : " << *name << std::endl;
        std::cout << "age : " << age << std::endl;
    }

    void setName(const std::string newName) {
        delete name;
        name = new std::string(newName);
    }

  private:
    int          age;
    std::string *name;
};

HumanValueLike &HumanValueLike::operator=(const HumanValueLike &rhs) {
    // check for self assignment
    if (this != &rhs) {
        // deallocate existing memory
        delete name;

        // deep copy for pointer to object
        name = new std::string(*rhs.name);

        // copy primitive member variable
        age = rhs.age;
    }
    return *this;
}

int main() {
    HumanValueLike obj1{"Lakshman", 26};
    HumanValueLike obj2 = obj1;

    obj1.print();
    obj2.print();

    obj2.setName("Lashi");

    obj1.print();
    obj2.print();
}