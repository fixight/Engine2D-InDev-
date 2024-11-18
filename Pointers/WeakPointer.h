#include "SmartPointer.h"

template <typename T>
class WeakPointer {
public:
    WeakPointer() : Pointer(nullptr), RefCount(nullptr), WeakRefCount(nullptr) {}
    
    WeakPointer(const SmartPointer<T>& smartPointer)
        : Pointer(smartPointer.Get()), RefCount(smartPointer.GetRefCount()), WeakRefCount(smartPointer.GetWeakRefCount()) {
        ++(*WeakRefCount);
    }

    WeakPointer(const WeakPointer& other)
        : Pointer(other.Pointer), RefCount(other.RefCount), WeakRefCount(other.WeakRefCount) {
        ++(*WeakRefCount);
    }

    ~WeakPointer() {
        release();
    }

    WeakPointer& operator=(const WeakPointer& other) {
        if (this != &other) {
            release();
            Pointer = other.Pointer;
            RefCount = other.RefCount;
            WeakRefCount = other.WeakRefCount;
            ++(*WeakRefCount);
        }
        return *this;
    }

    bool Expired() const {
        return !RefCount || *RefCount == 0;
    }

    SmartPointer<T> Lock() const {
        if (Expired()) {
            return SmartPointer<T>();
        }
        return SmartPointer<T>(*this);
    }

private:
    T* Pointer;
    int* RefCount;
    int* WeakRefCount;

    void release() {
        if (WeakRefCount && --(*WeakRefCount) == 0) {
            if (!RefCount || *RefCount == 0) {
                delete RefCount;
                delete WeakRefCount;
            }
        }
    }
};
