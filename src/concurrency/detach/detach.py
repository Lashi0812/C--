import threading

def hello():
    print("hello World")

def main():
    t = threading.Thread(target=hello,daemon=True)
    t.start()

if __name__ == "__main__":
    main()
    print("main thread is running")

    