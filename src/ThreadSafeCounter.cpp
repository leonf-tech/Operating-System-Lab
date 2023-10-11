#include <iostream>
#include <mutex>         //unique_lock
#include <shared_mutex>  //shared_mutex shared_lock
#include <thread>

std::mutex g_io_mtx;

class ThreadSafeCounter {
   private:
    mutable std::shared_mutex mutex_;
    size_t value_ = 0;

   public:
    ThreadSafeCounter(){};
    ~ThreadSafeCounter(){};

    size_t get() const {
        // 读者, 获取共享锁, 使用shared_lock
        std::shared_lock<std::shared_mutex> lck(mutex_);
        return value_;
    }

    size_t increment() {
        // 写者, 获取独占锁, 使用unique_lock
        std::unique_lock<std::shared_mutex> lck(mutex_);
        value_++;
        return value_;
    }

    void reset() {
        // 写者, 获取独占锁, 使用unique_lock
        std::unique_lock<std::shared_mutex> lck(mutex_);
        value_ = 0;
    }
};
ThreadSafeCounter counter;
void reader(int id) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::unique_lock<std::mutex> ulck(g_io_mtx);
    std::cout << "reader #" << id << " get value " << counter.get() << "\n";
}

void writer(int id) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::unique_lock<std::mutex> ulck(g_io_mtx);
    std::cout << "writer #" << id << " write value " << counter.increment()
              << "\n";
}

int use() {
    std::thread rth[10];
    std::thread wth[10];
    for (int i = 0; i < 4; i++) {
        rth[i] = std::thread(reader, i + 1);
    }
    for (int i = 0; i < 6; i++) {
        wth[i] = std::thread(writer, i + 1);
    }

    for (int i = 0; i < 4; i++) {
        rth[i].join();
    }
    for (int i = 0; i < 6; i++) {
        wth[i].join();
    }
    return 0;
}