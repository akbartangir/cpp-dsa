#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <cstddef>
#include <memory>
#include <utility>

template <typename T> class Vector
{
  public:
    /// Type definitions
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = T*;
    using const_iterator = const T*;

    /**
     * @brief Constructor an empty vector with optional initial capacity.
     * @param initialCapacity Initial capacity (default: 0, will allocate on first insertion).
     */
    explicit Vector(size_type initialCapacity = 0)
        : elements_{initialCapacity > 0 ? std::make_unique<T[]>(initialCapacity) : nullptr},
          capacity_{initialCapacity}, size_{0}
    {
    }

    /**
     * @brief Construct a vector with n default-constructed elements.
     * @param count Number of elements to construct.
     * @param value Value to initialize elements with.
     */
    Vector(size_type count, const T& value)
        : elements_{std::make_unique<T[]>(count)}, capacity_{count}, size_{count}
    {
        std::fill_n(elements_.get(), count, value);
    }

  private:
    static constexpr size_type DEFAULT_CAPACITY = 16; ///< Default initial capacity
    static constexpr size_type GROWTH_FACTOR = 2;     ///< Capacity growth multiplier

    std::unique_ptr<T[]> elements_; ///< Array holding vector elements
    size_type capacity_;            ///< Maximum capacity before reallocation
    size_type size_;                ///< Number of elements in the vector

    /**
     * @brief Ensure there is capacity for at least one more element.
     */
    void ensureCapacity()
    {
        if (size_ >= capacity_)
        {
            size_type newCapacity = capacity_ == 0 ? DEFAULT_CAPACITY : capacity_ * GROWTH_FACTOR;

            // Overflow check
            if (newCapacity <= capacity_ && capacity_ > 0)
            {
                newCapacity = capacity_ + 1;
            }

            reserve(newCapacity);
        }
    }
};

#endif // VECTOR_H
