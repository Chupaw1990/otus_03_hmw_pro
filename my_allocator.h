#pragma once
#include <iostream>

template <typename T, size_t allocator_size>
class custom_allocator {
   public:
    using value_type = T;

    custom_allocator() noexcept
        : pool(static_cast<u_int8_t *>(
              ::operator new(allocator_size * sizeof(T)))),
              pos{0} {}
    ~custom_allocator() { delete pool; };

    T *allocate(size_t n) {
        if (pos + n > allocator_size) {
            throw std::bad_alloc();
        }
        if (n == 0) {
            return nullptr;
        }
        int current = pos;
        pos += n;

        return reinterpret_cast<T*>(pool) + current;
    }
    void deallocate(T *p, size_t n) { ::operator delete(p, n * sizeof(T)); }

    template <typename U>
    struct rebind {
        using other = custom_allocator<U, allocator_size>;
    };

    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type;

   private:
    u_int8_t *pool;
    int pos;
};

template <typename T, size_t allocator_size, typename U, size_t S>
constexpr bool operator==(const custom_allocator<T, allocator_size> &a1,
                          const custom_allocator<U, S> &a2) {
    return a1.pool == a2.pool;
}

template <typename T, size_t allocator_size, typename U, size_t S>
constexpr bool operator!=(const custom_allocator<T, allocator_size> &a1,
                          const custom_allocator<U, S> &a2) {
    return a1.pool != a2.pool;
}