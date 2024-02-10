/*
Run : bazel run --run_under="valgrind" //src/copy_control:copy_control_for_dma

Small Demo for how the copy control used for DMA . For Simplicity we consider the String Vector.

class design for StrVec:

while adding the element
    check for free space
        Yes --> then construct the object in that space.
        No ---> Reallocate
            1. obtain new space
            2. move the existing element into that space
            3. free the old space
            4. add the new element

Member variable
1. element pointer --> this point to starting element in the vector
2. first_free pointer --> this point to the first free space in allocated memory
3. cap pointer --> this point to end of allocated memory

Member function
1. size --> for finding filled memory the allocated space
2. capacity --> for finding the total memory
3. chk_n_alloc --> if size == capacity then need to call reallocate
3. reallocation --> for reallocation the memory space
4. free --> for deallocate the DMA
*/

#include <cstddef>
#include <memory>
#include <string>
#include <utility>


class StrVec {
  public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(const StrVec &);              // copy constructor
    StrVec &operator=(const StrVec &);   // copy assignment
    ~StrVec();                           // destructor
    void push_back(const std::string &); // copy element

    std::size_t  size() { return first_free - elements; }
    std::size_t  capacity() { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }

  private:
    static std::allocator<std::string> alloc;

    std::pair<std::string *, std::string *> alloc_n_copy(std::string *, std::string *);

    void chk_n_alloc() {
        if (size() == capacity())
            reallocate();
    }
    void reallocate();
    void free();

    std::string *elements;
    std::string *first_free;
    std::string *cap;
};

std::allocator<std::string> StrVec::alloc;

void StrVec::push_back(const std::string &s) {
    chk_n_alloc();
    alloc.construct(first_free++, s);
}

std::pair<std::string *, std::string *> StrVec::alloc_n_copy(std::string *begin, std::string *end) {
    auto data = alloc.allocate(end - begin);
    return {data, std::uninitialized_copy(begin, end, data)};
}

void StrVec::free() {
    if (elements) {
        for (auto p = first_free; p != elements;) {
            alloc.destroy(--p);
        }
        alloc.deallocate(elements, cap - elements);
    }
}

// copy constructor
StrVec::StrVec(const StrVec &other) {
    auto new_data = alloc_n_copy(other.begin(), other.end());
    elements      = new_data.first;
    first_free = cap = new_data.second;
}

// copy assignment
StrVec &StrVec::operator=(const StrVec &rhs) {
    if (this != &rhs) {
        auto data = alloc_n_copy(rhs.begin(), rhs.end());
        free();
        elements   = data.first;
        first_free = cap = data.second;
    }
    return *this;
}

// destructor
StrVec::~StrVec() { free(); }

void StrVec::reallocate() {
    auto newCapacity = size() ? 2 * size() : 1;
    auto newData     = alloc.allocate(newCapacity);

    auto dest = newData;
    auto elem = elements;
    for (size_t i{0}; i != size(); ++i) {
        alloc.construct(dest++, std::move(*elem++));
    }
    free();
    elements = newData;
    first_free = dest;
    cap = elements + newCapacity;
}

int main(){
    StrVec vec1;
    vec1.push_back("hello");
    vec1.push_back("World");
    StrVec vec2(vec1);
    return 0;
}