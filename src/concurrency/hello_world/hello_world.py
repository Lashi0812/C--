import threading

def hello():
    print("Hello World")

def main():
    t = threading.Thread(target=hello)
    t.start()
    t.join()

if __name__ == "__main__":
    main()