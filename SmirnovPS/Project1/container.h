#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>
#include <stdexcept>

template<typename T>
class Container {
private:
	size_t size, capacity, step;
	T* elem;
	void reallocate();
public:
	Container(size_t, size_t);
	Container(size_t, size_t, const T&);
	Container(const Container<T>&);
	Container(Container<T>&&);
	Container() {};
	T& operator[](size_t);
	const T& operator[](size_t) const;
	const Container& operator = (const Container&);
	int find(T&) const;
	void push(T&);
	void push(T&&);
	void remove(T&);
	void remove(T&&);
	friend std::ostream& operator << (std::ostream& out, const Container<T>& c) {
		out << "Size = " << c.size << ", Capacity = " << c.capacity << ", Step = " << c.step << "\n";
		for (int i = 0; i < c.size; i++) {
			out << c.elem[i];
			if (i + 1 == c.size) break;
			out << " ";
		}
		return out;
	}
	~Container();
};

template<typename T>
Container<T>::~Container() {
	delete[]elem;
}

template<typename T>
Container<T>::Container(size_t cp, size_t st) : capacity(cp), size(0), step(st) {
	this->elem = new T[cp];
}

template<typename T>
Container<T>::Container(size_t cp, size_t st, const T& el) : capacity(cp), size(0), step(st) {
	this->elem = new T[cp];
	for (int i = 0; i < cp; i++)
		this->elem[i] = el;
}

template<typename T>
Container<T>::Container(const Container<T>& c) : size(c.size), capacity(c.capacity), step(c.step) {
	this->elem = new T[size];
	for (int i = 0; i < size; i++)
		elem[i] = c.elem[i];
}

template<typename T>
Container<T>::Container(Container<T>&& c) : size(c.size), capacity(c.capacity), step(c.step) {
	this->elem = c.elem;
	c.elem = nullptr;
	c.size = 0;
	c.capacity = 0;
}

template<typename T>
T& Container<T>::operator[](size_t ind) {
	if (ind >= this->size) throw std::out_of_range("Out of range");
	return this->elem[ind];
}

template<typename T>
const T& Container<T>::operator[](size_t ind) const {
	if (ind >= this->size) throw std::out_of_range("Out of range");
	return this->elem[ind];
}

template<typename T>
const Container<T>& Container<T>::operator = (const Container<T>& c) {
	if (this == &c) return *this;
	if (this->size != c.size) {
		delete[] this->elem;
		this->size = c.size;
		this->capacity = c.capacity;
		this->elem = new T[this->capacity];
	}
	for (int i = 0; i < size; i++)
		this->elem[i] = c.elem[i];
	return *this;
}

template<typename T>
int Container<T>::find(T& el) const {
	for (int i = 0; i < this->size; i++)
		if (this->elem[i] == el)
			return i;
	return -1;
}

template<typename T>
void Container<T>::remove(T& el) {
	int pos = this->find(el);
	if (pos == -1) throw std::runtime_error("Not found");
	this->elem[pos] = this->elem[--size];
}

template<typename T>
void Container<T>::remove(T&& el) {
	int pos = this->find(el);
	if (pos == -1) throw std::runtime_error("Not found");
	this->elem[pos] = this->elem[--size];
}

template<typename T>
void Container<T>::reallocate() {
	this->capacity += this->step;
	T* buf = new T[this->capacity];
	for (int i = 0; i < size; i++)
		buf[i] = elem[i];
	delete[] elem;
	elem = buf;
}

template<typename T>
void Container<T>::push(T& el) {
	if (this->size == this->capacity) reallocate();
	elem[size++] = el;
}

template<typename T>
void Container<T>::push(T&& el) {
	if (this->size == this->capacity) reallocate();
	elem[size++] = el;
}

template<typename T>
class Container<T*> {
private:
	size_t size, capacity, step;
	T** elem;
	void reallocate();
public:
	Container(size_t, size_t);
	Container(size_t, size_t, T*&);
	Container(const Container<T*>&);
	Container(Container<T*>&&);
	T*& operator[](size_t);
	const T*& operator[](size_t) const;
	const Container& operator=(const Container&);
	int find(T*&) const;
	void push(T*&);
	void push(T*&&);
	void remove(T*&);
	void remove(T*&&);
	friend std::ostream& operator<<(std::ostream& out, const Container<T*>& c) {
		out << "Size = " << c.size << ", Capacity = " << c.capacity << ", Step = " << c.step << "\n-------------------------------\n";
		for (int i = 0; i < c.size; i++) {
			out << *c.elem[i] << '\n';
		}
		out << "-------------------------------";
		return out;
	}
	~Container();
};

template<typename T>
Container<T*>::~Container() {
	for (int i = 0; i < this->size; i++) delete elem[i];
	delete[] elem;
}

template<typename T>
Container<T*>::Container(size_t cp, size_t st) : size(0), capacity(cp), step(st) {
	this->elem = new T * [capacity];
}

template<typename T>
Container<T*>::Container(size_t cp, size_t st, T*& el) : capacity(cp), step(st), size(cp) {
	this->elem = new T * [capacity];
	for (int i = 0; i < size; i++) elem[i] = new T(*el);
}

template<typename T>
T*& Container<T*>::operator[](size_t ind) {
	if (ind >= this->size) throw std::out_of_range("Out of range");
	return this->elem[ind];
}

template<typename T>
const T*& Container<T*>::operator[](size_t ind) const {
	if (ind >= this->size) throw std::out_of_range("Out of range");
	return this->elem[ind];
}

template<typename T>
const Container<T*>& Container<T*>::operator = (const Container<T*>& c) {
	if (this == &c) return *this;
	
	for (int i = 0; i < this->size; i++) delete this->elem[i];

	if (this->capacity != c.capacity) {
		delete[] this->elem;
		this->capacity = c.capacity;
		this->elem = new T * [this->capacity];
	}
	this->size = c.size;
	this->step = c.step;
	for (size_t i = 0; i < size; i++) this->elem[i] = new T(*c.elem[i]);
	return *this;
}

template<typename T>
int Container<T*>::find(T*& el) const {
	for (int i = 0; i < this->size; i++) {
		if (*elem[i] == *el) return i;
	}
	return -1;
}

template<typename T>
void Container<T*>::remove(T*& el) {
	int pos = this->find(el);
	if (pos == -1) throw std::runtime_error("Not found");
	delete this->elem[pos];
	this->elem[pos] = this->elem[--size];
}

template<typename T>
void Container<T*>::remove(T*&& el) {
	int pos = this->find(el);
	if (pos == -1) throw std::runtime_error("Not found");
	delete this->elem[pos];
	this->elem[pos] = this->elem[--size];
}

template<typename T>
void Container<T*>::reallocate() {
	this->capacity += this->step;
	T** buf = new T * [this->capacity];
	for (int i = 0; i < size; i++) buf[i] = elem[i];
	delete[] elem;
	elem = buf;
}

template<typename T>
void Container<T*>::push(T*& el) {
	if (this->size == this->capacity) reallocate();
	elem[size++] = new T(*el);
}

template<typename T>
void Container<T*>::push(T*&& el) {
	if (this->size == this->capacity) reallocate();
	elem[size++] = new T(*el);
}

template<typename T>
Container<T*>::Container(const Container<T*>& c) : size(c.size), capacity(c.capacity), step(c.step) {
	this->elem = new T * [capacity];
	for (int i = 0; i < size; i++) elem[i] = new T(*c.elem[i]);
}

template<typename T>
Container<T*>::Container(Container<T*>&& c) : size(c.size), capacity(c.capacity), step(c.step) {
	this->elem = c.elem;
	c.elem = nullptr;
	c.size = 0;
	c.capacity = 0;
}

#endif
