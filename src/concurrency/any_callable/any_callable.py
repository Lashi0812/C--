import threading

class AnyCallable:
    def __call__(self) -> None:
        print("this is called from member function")

if __name__ == "__main__":
    obj = AnyCallable()
    t = threading.Thread(target=obj)
    t.start()
    t.join()
    