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
		if ((size == MAX_VECTOR_SIZE) || (index<0)) throw std::logic_error("Unable to add element");
		if (size >= capacity) {
			size_t len = size_t(coefficient * size) + 1;
			this->resize(len);
		}
		for (size_t i = size; i > index; i--)
			data[i] = data[i - 1];
		data[index] = elem;
		size++;
	}

	void push_front(T elem) { insert(elem, 0); }

	void pop_front() {
		if (size == 0) throw std::logic_error("Unable to delete element");
		for (size_t i = 0; i < size; i++)
			data[i] = data[i + 1];
		size--;
	}

	void erase(int index) {
		if ((size == 0) || (index >= size) || (index < 0)) throw std::logic_error("Unable to delete element"); 
		for (size_t i = index; i < size; i++)
			data[i] = data[i + 1];
		size--;

	}

	Vector<T>& Vector<T>::operator=(const Vector& v)
	{
		if (this != &v) {
			if (v.capacity != capacity) {
				delete[] data;
				data = new T[v.size];
			}
			size = v.size;
			capacity = v.capacity;
			for (int i = 0; i < size; i++)
				data[i] = v.data[i];
		}
		return *this;
	}

	T& operator[](int index) { 
		if ((index>=size)||(index<0)) throw std::logic_error("Invalid index");
		return this->data[index]; 
	}
	
	T operator[](int index)const { return this->data[index]; }

	friend std::ostream& operator<< (std::ostream& out, const Vector& v) {
		for (size_t i = 0; i < v.size; i++)
			out << v.data[i] << ' ';
		return out;
	}

	friend std::istream& operator>>(std::istream& in, Vector& v)
	{
		for (size_t i = 0; i!='\n'; i++)
			in >> v.data[i];
		return in;
	}

	T GetElem(int index) { if ((index >= size) || (index < 0)) throw std::logic_error("Invalid index"); return data[index]; }
};

template <class T>
class Stack : public Vector<T> {
private:
	void push_front() {}
	void pop_front() {}
	void insert(T elem, int index) {}
	void erase(int index) {}
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

	size_t GetSize() { return size; }
	size_t GetCapacity() { return capacity; }
	T GetElement(int index) {return Vector<T>::GetElem(index); }

};

template <class T>
class Queue : public Vector<T> {
private:
	unsigned int front;
	unsigned int back;
	void insert(T elem, int index) {}
	void erase(int index) {}
	void pop_back() {}
	void pop_front() {}
	void push_back(T elem) {}
	void push_front(T elem) {}
	void resize(int n){}
public:
	Queue() :Vector() { front = 0; back = 0; }
	
	Queue(int n) :Vector(n) { front = 0; back = n-1; }
	
	~Queue(){}
	
	T Front() { return data[front]; }
	
	T Back() { return data[back]; }
	
	void push(T elem) {
	    back++;
		if (back == capacity) 
			back = 0;
		if (this->full() == 1)
			resize(size_t(coefficient * capacity) + 1);
		data[back] = elem;
		size++;
	}
	
	void pop() { 
		if (size == 0) throw std::logic_error("Unable to delete element");
		front++;
		size--;
		if (front == capacity) front = 0;
	}

	bool empty() {
		if (size == 0) return 1;
		else return 0;
	}

	bool full() {
		if (size == capacity) return 1;
		else return 0;
	}

};


template <class T>
class QueueOnTwoStacks : protected Stack<T> {
private:
	Stack<T> stack1,stack2;
public:
	QueueOnTwoStacks() {};

	QueueOnTwoStacks(int n) { Stack<T>stack1(n); Stack<T>stack2(n); }

	~QueueOnTwoStacks() { stack1.~Stack(); stack2.~Stack();}

	T Front() {
		if (stack2.empty() != 1) return stack2.top();
		else return stack1.GetElement(0);
	}

	T Back() {
		if ((stack1.empty() == 1)&&(stack2.empty() == 1))  throw std::logic_error("Queue is empty");
		if (stack1.empty() != 1) return stack1.top();
		else
			return stack2.GetElement(0);
	}

	void push(T elem) {
		stack1.push(elem);
		if (stack1.full()!=0) stack2.resize(stack1.GetCapacity());
	}

	void pop() {
		if (stack2.empty()==1)
			while (stack1.empty() != 1)
			{
				stack2.push(stack1.top());
				stack1.pop();
			};
		stack2.pop();
	}

	bool empty() {
		if ((stack1.empty() == 1) && (stack2.empty() == 1)) return 1;
		else return 0;
	}

	bool full() {
		if ((stack1.full() == 1) && (stack2.full() == 1)) return 1;
		else return 0;
	}

	size_t GetSize() { return(stack1.GetSize() + stack2.GetSize()); }

};