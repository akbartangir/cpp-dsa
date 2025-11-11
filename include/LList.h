#ifndef LLIST_H
#define LLIST_H

#include "Link.h"
#include "List.h"
#include <stdexcept>
#include <utility>

/**
 * @brief Linked list implementation with header node.
 * @tparam E The type of elements stored in the list.
 *
 * Implements the List interface using a singly-linked list with a header node.
 * The header node simplifies boundary conditions. The cursor points to the node
 * BEFORE the current element, making insertion efficient.
 *
 * Time complexities:
 * - insert/append: O(1)
 * - remove: O(1)
 * - moveToPos/currPos: O(n)
 * - prev: O(n) (requires traversal from head)
 */
template <typename E> class LList : public List<E>
{
  private:
    Link<E>* head_;    ///< Header node (dummy node before first element)
    Link<E>* tail_;    ///< Pointer to last node
    Link<E>* curr_;    ///< Points to node before current element
    std::size_t size_; ///< Number of elements in the list

    /**
     * @brief Initialize an empty list with header node.
     */
    void init()
    {
        head_ = new Link<E>();
        tail_ = curr_ = head_;
        size_ = 0;
    }

    /**
     * @brief Delete all nodes including header.
     */
    void removeAll() noexcept
    {
        Link<E>* current = head_;
        while (current != nullptr)
        {
            Link<E>* next = current->next;
            delete current;
            current = next;
        }
        head_ = tail_ = curr_ = nullptr;
        size_ = 0;
    }

    /**
     * @brief Deep copy from another list.
     * @param other The list to copy from.
     */
    void copyFrom(const LList& other)
    {
        init();

        // Copy all elements
        Link<E>* otherNode = other.head_->next;
        while (otherNode != nullptr)
        {
            append(otherNode->element);
            otherNode = otherNode->next;
        }

        // Set cursor to same relative position
        std::size_t otherPos = other.currPos();
        moveToPos(otherPos);
    }

  public:
    /**
     * @brief Construct an empty linked list.
     */
    LList()
    {
        init();
    }

    /**
     * @brief Copy constructor - performs deep copy.
     * @param other The list to copy from.
     */
    LList(const LList& other)
    {
        copyFrom(other);
    }

    /**
     * @brief Copy assignment operator - performs deep copy.
     * @param other The list to copy from.
     * @return Reference to this list.
     */
    LList& operator=(const LList& other)
    {
        if (this != &other)
        {
            removeAll();
            copyFrom(other);
        }
        return *this;
    }

    /**
     * @brief Move constructor.
     * @param other The list to move from.
     */
    LList(LList&& other) noexcept
        : head_{other.head_}, tail_{other.tail_}, curr_{other.curr_}, size_{other.size_}
    {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.curr_ = nullptr;
        other.size_ = 0;
    }

    /**
     * @brief Move assignment operator.
     * @param other The list to move from.
     * @return Reference to this list.
     */
    LList& operator=(LList&& other) noexcept
    {
        if (this != &other)
        {
            removeAll();

            head_ = other.head_;
            tail_ = other.tail_;
            curr_ = other.curr_;
            size_ = other.size_;

            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.curr_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    /**
     * @brief Destructor - cleans up all nodes.
     */
    ~LList() override
    {
        removeAll();
    }

    /**
     * @brief Clear the list, removing all elements.
     */
    void clear() override
    {
        removeAll();
        init();
    }

    /**
     * @brief Insert an element at the current position.
     * @param item The element to insert.
     *
     * The new element becomes the current element.
     * Time complexity: O(1).
     */
    void insert(const E& item) override
    {
        curr_->next = new Link<E>(item, curr_->next);
        if (tail_ == curr_)
        {
            tail_ = curr_->next;
        }
        ++size_;
    }

    /**
     * @brief Append an element at the end of the list.
     * @param item The element to append.
     *
     * Time complexity: O(1).
     */
    void append(const E& item) override
    {
        tail_->next = new Link<E>(item, nullptr);
        tail_ = tail_->next;
        ++size_;
    }

    /**
     * @brief Remove and return the current element.
     * @return The removed element.
     * @throws std::out_of_range if no element is at current position.
     *
     * After removal, the cursor points to the node before what was
     * the next element (which becomes the new current element).
     * Time complexity: O(1).
     */
    E remove() override
    {
        if (curr_->next == nullptr)
        {
            throw std::out_of_range("No element at current position");
        }

        E item = std::move(curr_->next->element);
        Link<E>* temp = curr_->next;

        if (tail_ == curr_->next)
        {
            tail_ = curr_;
        }

        curr_->next = curr_->next->next;
        delete temp;
        --size_;
        return item;
    }

    /**
     * @brief Move cursor to the start of the list.
     *
     * Time complexity: O(1).
     */
    void moveToStart() noexcept override
    {
        curr_ = head_;
    }

    /**
     * @brief Move cursor to the end of the list.
     *
     * After this operation, there is no current element.
     * Time complexity: O(1).
     */
    void moveToEnd() noexcept override
    {
        curr_ = tail_;
    }

    /**
     * @brief Move cursor one position to the left.
     *
     * No change if already at the beginning.
     * Time complexity: O(n) - must traverse from head.
     */
    void prev() noexcept override
    {
        if (curr_ == head_)
        {
            return;
        }

        Link<E>* temp = head_;
        while (temp->next != curr_)
        {
            temp = temp->next;
        }
        curr_ = temp;
    }

    /**
     * @brief Move cursor one position to the right.
     *
     * No change if already at the end.
     * Time complexity: O(1).
     */
    void next() noexcept override
    {
        if (curr_ != tail_)
        {
            curr_ = curr_->next;
        }
    }

    /**
     * @brief Get the number of elements in the list.
     * @return The number of elements.
     */
    [[nodiscard]] std::size_t length() const noexcept override
    {
        return size_;
    }

    /**
     * @brief Get the current cursor position.
     * @return The position (0-based index).
     *
     * Time complexity: O(n) - must traverse from head.
     */
    [[nodiscard]] std::size_t currPos() const noexcept override
    {
        Link<E>* temp = head_;
        std::size_t index = 0;

        while (temp != curr_)
        {
            temp = temp->next;
            ++index;
        }

        return index;
    }

    /**
     * @brief Set the cursor position.
     * @param pos The position to set (0 <= pos <= size).
     * @throws std::out_of_range if pos is out of valid range.
     *
     * Time complexity: O(n).
     */
    void moveToPos(std::size_t pos) override
    {
        if (pos > size_)
        {
            throw std::out_of_range("Position out of range");
        }

        curr_ = head_;
        for (std::size_t i = 0; i < pos; ++i)
        {
            curr_ = curr_->next;
        }
    }

    /**
     * @brief Get the element at the current position.
     * @return Const reference to the current element.
     * @throws std::out_of_range if no element is at current position.
     */
    [[nodiscard]] const E& getValue() const override
    {
        if (curr_->next == nullptr)
        {
            throw std::out_of_range("No element at current position");
        }
        return curr_->next->element;
    }
};

#endif // LLIST_H
