#include <iostream>

const int MAX_VECTOR_SIZE = 100000000;
const double coefficient = 1.3;

template <class T>
class Vector
{
protected:
	T* data;
	size_t size;
	size_t capacity;
public:
	Vector() { data = nullptr; size = 0; capacity = 0; }
	
	~Vector() { delete[]data; data = nullptr; }
	
	Vector(int n) {
		if ((n > MAX_VECTOR_SIZE) || (n < 0)) throw std::logic_error("Invalid size");
		size = n;
		capacity = n;
		data = new T[n];
		for (int i = 0; i < n; i++)
			data[i] = 0;
	}

	Vector(const Vector& v) {
		delete[]data;
		size = v.size;
		capacity = v.capacity;
		T* data = new T[size];
		for (size_t i = 0; i < size; i++)
			data[i] = v.data[i];
	}

	int GetSize() { return size; }

	void push_back(T elem) {
		if (size == MAX_VECTOR_SIZE) throw std::logic_error("Unable to add element");
		if (size >= capacity) {
			size_t len = size_t(coefficient * size) + 1;
			this->resize(len);
		}
		data[size] = elem;
		size++;
	}

	void pop_back() {
		if (size==0) throw std::logic_error("Unable to delete element");
		this->resize(size - 1);
	}

	void resize(int n) {
		if ((n > MAX_VECTOR_SIZE) || (n < 0)) throw std::logic_error("Invalid size");
		T* temp = new T[n];
		if (size >= n) {
			for (size_t i = 0; i < n; i++)
				temp[i] = data[i];
			size = n;
		}
		else {
			for (size_t i = 0; i < size; i++)
				temp[i] = data[i];
		}
		delete[] data;
		capacity = n;
		data = temp;
	}

	void insert(T elem, int index) {
		if ((size == MAX_VECTOR_SIZE) || (index > size)||(index<0)) throw std::logic_error("Unable to add element");
		if (size >= capacity) {
			size_t len = size_t(coefficient * size) + 1;
			this->resize(len);
		}
		for (size_t i = size; i > index - 1; i--)
			data[i] = data[i - 1];
		data[index - 1] = elem;
		size++;
	}

	void push_front(T elem) {
		if (size == MAX_VECTOR_SIZE) throw std::logic_error("Unable to add element");
		if (size >= capacity) {
			size_t len = size_t(coefficient * size) + 1;
			this->resize(len);
		}
		for (size_t i = size; i > 0; i--)
			data[i] = data[i - 1];
		data[0] = elem;
		size++;
	}

	void pop_front() {
		if (size == 0) throw std::logic_error("Unable to delete element");
		for (size_t i = 0; i < size; i++)
			data[i] = data[i + 1];
		size--;
	}

	void erase(int index) {
		if ((size == 0)||(index>=size) || (index < 0)) throw std::logic_error("Unable to delete element");
		T* temp = new T[capacity];
		for (int i = 0; i < index - 1; i++)
			temp[i] = data[i];
		for (int i = index - 1; i < size; i++)
			temp[i] = data[i + 1];
		delete[]data;
		data = temp;
		size--;
	}

	T& operator[](int index) { 
		if (index>=size) throw std::logic_error("Invalid index");
		return this->data[index]; 
	}
	
	T operator[](int index)const { return this->data[index]; }

	friend std::ostream& operator<< (std::ostream& out, const Vector& v) {
		for (size_t i = 0; i < v.size; i++)
			out << v.data[i] << ' ';
		return out;
	}

};

template <class T>
class Stack : public Vector<T> {
public:
	Stack():Vector() {}
	Stack(int n) :Vector(n) {}
	~Stack(){}
	T top() { return data[size - 1]; }
	void push(T elem) { Vector<T>::push_back(elem); }
	void pop() { Vector<T>::pop_back(); }
	
	bool empty() {
		if (size == 0) return 1;
		else return 0;
	}

	bool full() {
		if (size == capacity) return 1;
		else return 0;
	}
};