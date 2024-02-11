#include <iostream>
#include <thread>
class AnyCallable{
    public:
        void operator()(){
            std::cout << "this is from member function" << std::endl;
        }
};

int main(){
    AnyCallable obj;
    std::thread t(obj);
    t.join();
}