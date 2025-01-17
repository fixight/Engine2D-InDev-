#include <mutex>

class GlobalIDGenerator {
public:
    static GlobalIDGenerator& GetInstance() {
        static GlobalIDGenerator instance;
        return instance;
    }

    uint64_t GetNextID() {
        std::lock_guard<std::mutex> lock(mutex);
        return idCounter++;
    }

private:
    GlobalIDGenerator() : idCounter(1) {}
    ~GlobalIDGenerator() = default;

    uint64_t idCounter;
    std::mutex mutex;
};


