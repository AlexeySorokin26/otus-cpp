#pragma once

// Container -> Allocator -> operator new -> malloc -> OS

#include <new>  // Для std::bad_alloc

template<typename T>
struct allocator {
	allocator() {}
	allocator(const allocator& allocator) {}

	// only allocate memory, not create new objs
	T* allocate(size_t count) {
		return reinterpret_cast<T*>(new char[count * sizeof(T)]);
	}
	// free memory
	void deallocate(T* ptr, size_t count) {
		delete[] reinterpret_cast<char*>(ptr);
	}
	template<typename U, typename... Args>
	void construct(U* ptr, const Args&... args) {
		new (ptr) U(args...);
	}
	void destroy(T* ptr) {
		ptr->~T();
	}
};

// Оператор сравнения аллокаторов (всегда false)
template <class T, class U>
constexpr bool operator==(const allocator<T>&, const allocator<U>&) noexcept {
	return false;  // Разные аллокаторы никогда не равны
}

// Оператор неравенства аллокаторов (всегда true)
template <class T, class U>
constexpr bool operator!=(const allocator<T>&, const allocator<U>&) noexcept {
	return true;
}

// allocate memory and give a bit every time we ask him
template<typename T>
class pool_allocator {
public:
	pool_allocator(size_t count) :
		max_count(count), current(0),
		pool(reinterpret_cast<T*>(new char[count * sizeof(T)]))
	{
		if (!pool) throw std::bad_alloc();
	}

	~pool_allocator() {
		if (pool) delete[] reinterpret_cast<char*>(pool);
	}

	T* get_next() {
		if (current >= max_count) return nullptr;
		return &pool[current++];
	}

	size_t used() const { return current; }

private:
	T* pool;
	size_t max_count;
	size_t current;
};

struct TestData {
	int a;
	double b;
	char padding[32];

	TestData(int a, double b) : a(a), b(b) {}
};

// stack allocator 
// allocate all on stack for example for std::map
// we don't want to call new everytime we add element 
// for std::vector initally we just call new for 2, 4, ... elements
// but for every new element in map we have to call new (by default)
// example:
// std::array<char, 1000000> arr;
// StackAllocator<int> alloc(arr);
// std::list<int, StackAllocator<int>> lst;
