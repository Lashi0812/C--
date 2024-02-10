/*
A class behaves like a pointer, copying an instance results in multiple instances sharing the same
underlying data. Changes to one instance affect all instances sharing the same data.
We can use the shared pointer to achieve class like Pointer. but here are doing manually by using
reference count

1. Copy Constructor and Assignment --> must copy the pointer not object
2. We need maintain the reference counter when doing the copy constructor and Assignment.
3. Reference counter should be dynamically allocated object so that we maintain the count across all
shared object.
4. Copy Constructor increase the ref count.
5. Copy Assignment
    a. consider lhs and rhs two object
    b. in cp assignment we copy the rhs into lhs
    c. so we have to decrement the lhs and increment the rhs , ref count respectively
    d. if lhs ref count go zero we have to delete DAO(dynamic Allocated Memory)
6. Destructor delete the dynamically allocated memory if ref count is 0
*/

#include <cstddef>
#include <iostream>
#include <string>

class HumanPointerLike {
  public:
    HumanPointerLike(const std::string &name, const int age)
        : name(new std::string(name)), age(age), ref_count(new std::size_t(1)) {}

    HumanPointerLike(const HumanPointerLike &other)
        /*copy the pointer not the object*/
        : name(other.name), age(other.age), ref_count(other.ref_count) {
        ++*ref_count; // increment the ref count
    }

    HumanPointerLike &operator=(const HumanPointerLike &);
    ~HumanPointerLike();

    void print() {
        std::cout << "name : " << *name << std::endl;
        std::cout << "age : " << age << std::endl;
    }

    void setName(const std::string &newName) { *name = newName; }

  private:
    std::string *name;
    int          age;
    std::size_t *ref_count;
};

HumanPointerLike::~HumanPointerLike() {
    if (--*ref_count /*decrement and check*/ == 0) {
        delete name;
        delete ref_count;
    }
}

HumanPointerLike &HumanPointerLike::operator=(const HumanPointerLike &rhs) {
    if (this != &rhs) {
        ++*rhs.ref_count; // increment rhs ref count
        if (--*ref_count /*decrement and check the lhs*/ == 0) {
            delete name;
            delete ref_count;
        }
        name      = rhs.name;
        age       = rhs.age;
        ref_count = rhs.ref_count;
    }
    return *this;
}

int main() {
    HumanPointerLike obj1("Lakshman", 26);
    HumanPointerLike obj2(obj1);
    HumanPointerLike obj3(obj1);

    obj1.print();
    obj2.print();
    obj3.print();

    obj2.setName("Lashi");

    obj1.print();
    obj2.print();
    obj3.print();
}
