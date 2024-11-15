#pragma once

//����� ��������� ������� ������ ����� �������� ������� �� ���� ��������� , ����� ������ ��� RefCount = 0 ������ �� ���� ����������� �� ������ � ����� ���� ������
//���� ��������� ����� ������������ ����� ������ ���� ������� ���� �������� , ������ ��� ������������ ����� ��� ��������������
//���� ��� ������ ����� ����� ������� ��������� �� ������ , �� ��� ������������� ��� �� ������� ����� ������������ weak pointer

template <typename T>
class SmartPointer
{

	
	SmartPointer& operator=(const SmartPointer& other) {
		if (this != &other) {
			release();
			Pointer = other.Pointer;
			RefCount = other.RefCount;
			++(*RefCount);
		}
		return *this;
	}


public:
	SmartPointer() : Pointer(nullptr), RefCount(new int(0)) {}

	SmartPointer(T* ptr) : Pointer(ptr), RefCount(new int(1)) {}

	~SmartPointer() {
		release();
	}

	
	SmartPointer(const SmartPointer& other) : Pointer(other.Pointer), RefCount(other.RefCount) {
		++(*RefCount); 
	}






private:
	int* RefCount;

	T* Pointer;

	void release() {
		if (--(*RefCount) == 0) {
			delete Pointer;
			delete RefCount;
		}
	}

	



};

