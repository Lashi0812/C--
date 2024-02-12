#include <mutex>
class Tensor {};
void swap(Tensor &lhs, Tensor &rhs) {}

class Layer {
  public:
    Layer(Tensor &t) : tensor(t){};
    friend void swap(Layer &lhs, Layer &rhs) {
        if(&lhs == &rhs)
            return;
        // std::lock(lhs.m, rhs.m);
        // std::lock_guard<std::mutex> lock_lhs(lhs.m, std::adopt_lock);
        // std::lock_guard<std::mutex> lock_rhs(rhs.m, std::adopt_lock);

        std::scoped_lock guard(lhs.m,rhs.m);
        swap(lhs.tensor, rhs.tensor);
    }

  private:
    Tensor     tensor;
    std::mutex m;
};

int main(){}