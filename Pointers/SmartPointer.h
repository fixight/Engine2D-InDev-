#pragma once

//����� ��������� ������� ������ ����� �������� ������� �� ���� ��������� , ����� ������ ��� RefCount = 0 ������ �� ���� ����������� �� ������ � ����� ���� ������
//���� ��������� ����� ������������ ����� ������ ���� ������� ���� �������� , ������ ��� ������������ ����� ��� ��������������
//���� ��� ������ ����� ����� ������� ��������� �� ������ , �� ��� ������������� ��� �� ������� ����� ������������ weak pointer

template <typename T>
class SmartPointer {
public:
    SmartPointer() : Pointer(nullptr), RefCount(new int(1)) {}

    
    explicit SmartPointer(T* ptr) : Pointer(ptr), RefCount(new int(1)) {}

    
    ~SmartPointer() {
        release();
    }

    
    SmartPointer(const SmartPointer& other) 
        : Pointer(other.Pointer), RefCount(other.RefCount) {
        if (Pointer) {
            ++(*RefCount);
        }
    }

    
    SmartPointer& operator=(const SmartPointer& other) {
        if (this != &other) {
            release();
            Pointer = other.Pointer;
            RefCount = other.RefCount;
            if (Pointer) {
                ++(*RefCount);
            }
        }
        return *this;
    }
    
    T* operator->() const {
        return Pointer;
    }

    
    T& operator*() const {
        return *Pointer;
    }
    
    T* Get() const {
        return Pointer;
    }

    int* GetRefCount() const {return RefCount;}

    int* GetWeakRefCount() const {return WeakRefCount;}

private:
    T* Pointer;      
    int* RefCount;
    int* WeakRefCount;

    void release() {
        if (RefCount && --(*RefCount) == 0) {
            //delete Pointer;   
            delete RefCount;  
        }
    }
};

