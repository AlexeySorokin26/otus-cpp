#include <memory>
#include <iostream>
#include <map>
#include <vector>

template <typename T>
class pool_allocator {
public:
    using value_type = T;

    pool_allocator(size_t size = 10) : m_size(size), m_pool(new char[size * sizeof(T)]), m_used(size, false) {}

    template <typename U>
    pool_allocator(const pool_allocator<U>& other) : m_size(other.m_size), m_pool(new char[other.m_size * sizeof(T)]), m_used(other.m_size, false) {}

    ~pool_allocator() {
        delete[] static_cast<char*>(m_pool);
    }

    T* allocate(size_t n) {
        if (n != 1) throw std::bad_alloc();

        for (size_t i = 0; i < m_size; ++i) {
            if (!m_used[i]) {
                m_used[i] = true;
                return reinterpret_cast<T*>(static_cast<char*>(m_pool) + i * sizeof(T));
            }
        }
        throw std::bad_alloc();
    }

    void deallocate(T* p, size_t n) noexcept {
        if (!p || n != 1) return;

        size_t index = (reinterpret_cast<char*>(p) - static_cast<char*>(m_pool)) / sizeof(T);
        if (index < m_size) {
            m_used[index] = false;
        }
    }

    template <typename U>
    struct rebind {
        using other = pool_allocator<U>;
    };

    template <typename U>
    bool operator==(const pool_allocator<U>& other) const noexcept {
        return this == &other;
    }

    template <typename U>
    bool operator!=(const pool_allocator<U>& other) const noexcept {
        return !(*this == other);
    }

private:
    size_t m_size;
    void* m_pool;
    std::vector<bool> m_used;

    template <typename U>
    friend class pool_allocator;
};

int main() {
    try {
        pool_allocator<std::pair<const int, int>> alloc(20);

        std::map<int, int, std::less<int>,
            pool_allocator<std::pair<const int, int>>> my_map(alloc);

        for (int i = 0; i < 10; ++i) {
            my_map[i] = i * i;
        }

        for (const auto& [key, value] : my_map) {
            std::cout << key << ": " << value << "\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}