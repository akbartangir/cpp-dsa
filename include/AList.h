#ifndef ALIST_H
#define ALIST_H

#include "List.h"
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <utility>

/**
 * @brief Array-based list implementation.
 * @tparam E The type of elements stored in the list.
 *
 * Implements the List interface using a dynamically-resizable array.
 * Provides O(1) access and O(n) insertion/deletion at arbitrary positions.
 */
template <typename E> class AList : public List<E>
{
  private:
    static constexpr std::size_t DEFAULT_CAPACITY = 10; ///< Default initial capacity
    static constexpr std::size_t GROWTH_FACTOR = 2;     ///< Capacity growth multiplier

    std::unique_ptr<E[]> listArray_; ///< Array holding list elements
    std::size_t capacity_;           ///< Maximum capacity before reallocation
    std::size_t size_;               ///< Number of elements in the list
    std::size_t curr_;               ///< Position of current element

    /**
     * @brief Resize the internal array to accommodate more elements.
     * @param newCapacity The new capacity (must be >= size_).
     */
    void resize(std::size_t newCapacity)
    {
        if (newCapacity < size_)
        {
            newCapacity = size_;
        }

        auto newArray = std::make_unique<E[]>(newCapacity);

        // Move elements to new array
        for (std::size_t i = 0; i < size_; ++i)
        {
            newArray[i] = std::move(listArray_[i]);
        }

        listArray_ = std::move(newArray);
        capacity_ = newCapacity;
    }

    /**
     * @brief Ensure there is capacity for at least one more element.
     */
    void ensureCapacity()
    {
        if (size_ >= capacity_)
        {
            std::size_t newCapacity = capacity_ * GROWTH_FACTOR;
            if (newCapacity <= capacity_)
            { // Overflow check
                newCapacity = capacity_ + 1;
            }
            resize(newCapacity);
        }
    }

  public:
    /**
     * @brief Construct an empty list with given initial capacity.
     * @param initialCapacity Initial capacity (default: DEFAULT_CAPACITY).
     */
    explicit AList(std::size_t initialCapacity = DEFAULT_CAPACITY)
        : listArray_{std::make_unique<E[]>(initialCapacity)}, capacity_{initialCapacity}, size_{0},
          curr_{0}
    {
    }

    /**
     * @brief Copy constructor - performs deep copy.
     * @param other The list to copy from.
     */
    AList(const AList& other)
        : listArray_{std::make_unique<E[]>(other.capacity_)}, capacity_{other.capacity_},
          size_{other.size_}, curr_{other.curr_}
    {
        std::copy_n(other.listArray_.get(), size_, listArray_.get());
    }

    /**
     * @brief Copy assignment operator - performs deep copy.
     * @param other The list to copy from.
     * @return Reference to this list.
     */
    AList& operator=(const AList& other)
    {
        if (this != &other)
        {
            auto newArray = std::make_unique<E[]>(other.capacity_);
            std::copy_n(other.listArray_.get(), other.size_, newArray.get());

            listArray_ = std::move(newArray);
            capacity_ = other.capacity_;
            size_ = other.size_;
            curr_ = other.curr_;
        }
        return *this;
    }

    /**
     * @brief Move constructor.
     * @param other The list to move from.
     */
    AList(AList&& other) noexcept
        : listArray_{std::move(other.listArray_)}, capacity_{other.capacity_}, size_{other.size_},
          curr_{other.curr_}
    {
        other.capacity_ = 0;
        other.size_ = 0;
        other.curr_ = 0;
    }

    /**
     * @brief Move assignment operator.
     * @param other The list to move from.
     * @return Reference to this list.
     */
    AList& operator=(AList&& other) noexcept
    {
        if (this != &other)
        {
            listArray_ = std::move(other.listArray_);
            capacity_ = other.capacity_;
            size_ = other.size_;
            curr_ = other.curr_;

            other.capacity_ = 0;
            other.size_ = 0;
            other.curr_ = 0;
        }
        return *this;
    }

    /// Destructor - unique_ptr handles cleanup automatically
    ~AList() override = default;

    /**
     * @brief Clear the list, removing all elements.
     */
    void clear() override
    {
        listArray_ = std::make_unique<E[]>(capacity_);
        size_ = 0;
        curr_ = 0;
    }

    /**
     * @brief Insert an element at the current position.
     * @param item The element to insert.
     *
     * All elements from current position onwards are shifted right.
     * Time complexity: O(n) where n is the number of elements after current position.
     */
    void insert(const E& item) override
    {
        ensureCapacity();

        // Shift elements to the right
        for (std::size_t i = size_; i > curr_; --i)
        {
            listArray_[i] = std::move(listArray_[i - 1]);
        }

        listArray_[curr_] = item;
        ++size_;
    }

    /**
     * @brief Append an element at the end of the list.
     * @param item The element to append.
     *
     * Time complexity: O(1) amortized.
     */
    void append(const E& item) override
    {
        ensureCapacity();
        listArray_[size_++] = item;
    }

    /**
     * @brief Remove and return the current element.
     * @return The removed element.
     * @throws std::out_of_range if no element is at current position.
     *
     * Time complexity: O(n) where n is the number of elements after current position.
     */
    E remove() override
    {
        if (curr_ >= size_)
        {
            throw std::out_of_range("No element at current position");
        }

        E item = std::move(listArray_[curr_]);

        // Shift elements to the left
        for (std::size_t i = curr_; i < size_ - 1; ++i)
        {
            listArray_[i] = std::move(listArray_[i + 1]);
        }

        --size_;
        return item;
    }

    /// @brief Move cursor to the start of the list.
    void moveToStart() noexcept override
    {
        curr_ = 0;
    }

    /// @brief Move cursor to the end of the list (one past the last element).
    void moveToEnd() noexcept override
    {
        curr_ = size_;
    }

    /// @brief Move cursor one position to the left (no change if already at start).
    void prev() noexcept override
    {
        if (curr_ > 0)
        {
            --curr_;
        }
    }

    /// @brief Move cursor one position to the right (no change if already at end).
    void next() noexcept override
    {
        if (curr_ < size_)
        {
            ++curr_;
        }
    }

    /// @brief Get the number of elements in the list.
    [[nodiscard]] std::size_t length() const noexcept override
    {
        return size_;
    }

    /// @brief Get the current cursor position.
    [[nodiscard]] std::size_t currPos() const noexcept override
    {
        return curr_;
    }

    /**
     * @brief Set the cursor position.
     * @param pos The position to set (0 <= pos <= size).
     * @throws std::out_of_range if pos is out of valid range.
     */
    void moveToPos(std::size_t pos) override
    {
        if (pos > size_)
        {
            throw std::out_of_range("Position out of range");
        }
        curr_ = pos;
    }

    /**
     * @brief Get the element at the current position.
     * @return Const reference to the current element.
     * @throws std::out_of_range if no element is at current position.
     */
    [[nodiscard]] const E& getValue() const override
    {
        if (curr_ >= size_)
        {
            throw std::out_of_range("No element at current position");
        }
        return listArray_[curr_];
    }

    /**
     * @brief Get the current capacity of the internal array.
     * @return The capacity.
     */
    [[nodiscard]] std::size_t capacity() const noexcept
    {
        return capacity_;
    }

    /**
     * @brief Reserve space for at least n elements.
     * @param n The desired capacity.
     *
     * If n > current capacity, reallocates to capacity of at least n.
     * Does not change the size or contents of the list.
     */
    void reserve(std::size_t n)
    {
        if (n > capacity_)
        {
            resize(n);
        }
    }

    /**
     * @brief Shrink the capacity to fit the current size.
     *
     * Reduces memory usage by reallocating to the minimum needed capacity.
     */
    void shrink_to_fit()
    {
        if (capacity_ > size_)
        {
            std::size_t newCapacity = size_ > 0 ? size_ : 1;
            resize(newCapacity);
        }
    }
};

#endif // ALIST_H