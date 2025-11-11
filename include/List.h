#ifndef LIST_H
#define LIST_H

#include <cstddef>

/**
 * @brief Abstract base class for list ADT.
 * @tparam E The type of elements stored in the list.
 *
 * Provides a common interface for list implementations with cursor-based traversal.
 */
template <typename E> class List
{
  public:
    /// Default constructor
    List() = default;

    /// Virtual destructor for proper cleanup of derived classes
    virtual ~List() = default;

    // Delete copy operations to prevent slicing
    List(const List&) = delete;
    List& operator=(const List&) = delete;

    // Allow move operations (derived classes should implement as needed)
    List(List&&) noexcept = default;
    List& operator=(List&&) noexcept = default;

    /**
     * @brief Clear contents from the list, making it empty.
     */
    virtual void clear() = 0;

    /**
     * @brief Insert an element at the current location.
     * @param item The element to be inserted.
     */
    virtual void insert(const E& item) = 0;

    /**
     * @brief Append an element at the end of the list.
     * @param item The element to be appended.
     */
    virtual void append(const E& item) = 0;

    /**
     * @brief Remove and return the current element.
     * @return The element that was removed.
     * @throws std::out_of_range if no element is at current position.
     */
    virtual E remove() = 0;

    /**
     * @brief Set the current position to the start of the list.
     */
    virtual void moveToStart() noexcept = 0;

    /**
     * @brief Set the current position to the end of the list.
     */
    virtual void moveToEnd() noexcept = 0;

    /**
     * @brief Move the current position one step left.
     * No change if already at beginning.
     */
    virtual void prev() noexcept = 0;

    /**
     * @brief Move the current position one step right.
     * No change if already at end.
     */
    virtual void next() noexcept = 0;

    /**
     * @brief Get the number of elements in the list.
     * @return The number of elements in the list.
     */
    [[nodiscard]] virtual std::size_t length() const noexcept = 0;

    /**
     * @brief Get the position of the current element.
     * @return The position of the current element.
     */
    [[nodiscard]] virtual std::size_t currPos() const noexcept = 0;

    /**
     * @brief Set current position.
     * @param pos The position to make current.
     * @throws std::out_of_range if pos is out of valid range.
     */
    virtual void moveToPos(std::size_t pos) = 0;

    /**
     * @brief Get the current element.
     * @return Const reference to the current element.
     * @throws std::out_of_range if no element is at current position.
     */
    [[nodiscard]] virtual const E& getValue() const = 0;

    /**
     * @brief Check if the list is empty.
     * @return true if the list is empty, false otherwise.
     */
    [[nodiscard]] virtual bool isEmpty() const noexcept
    {
        return length() == 0;
    }
};

#endif // LIST_H
