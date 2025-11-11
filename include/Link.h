// Singly linked list node
#ifndef LINK_H
#define LINK_H

#include <utility>

/**
 * @brief A singly linked list node.
 * @tparam E The type of element stored in the node.
 *
 * Note: Uses raw pointers to allow for flexible memory management
 * in both LList implementations. The owning container is responsible
 * for proper memory management.
 */
template <typename E> class Link
{
  public:
    E element;  ///< The data element stored in this node
    Link* next; ///< Pointer to the next node in the list

    /**
     * @brief Default constructor - creates a node with default element value.
     */
    Link() : element{}, next{nullptr} {}

    /**
     * @brief Constructs a node with the given element and next pointer.
     * @param elem The element to store in this node.
     * @param nextPtr Pointer to the next node (default: nullptr).
     */
    explicit Link(const E& elem, Link* nextPtr = nullptr) : element{elem}, next{nextPtr} {}

    /**
     * @brief Constructs a node with a moved element and next pointer.
     * @param elem The element to move into this node.
     * @param nextPtr Pointer to the next node (default: nullptr).
     */
    explicit Link(E&& elem,
                  Link* nextPtr = nullptr) noexcept(std::is_nothrow_move_constructible_v<E>)
        : element{std::move(elem)}, next{nextPtr}
    {
    }

    // Copying links would create ambiguous ownership - delete copy operations
    Link(const Link&) = delete;
    Link& operator=(const Link&) = delete;

    // Moving is allowed
    Link(Link&& other) noexcept(std::is_nothrow_move_constructible_v<E>)
        : element{std::move(other.element)}, next{other.next}
    {
        other.next = nullptr;
    }

    Link& operator=(Link&& other) noexcept(std::is_nothrow_move_assignable_v<E>)
    {
        if (this != &other)
        {
            element = std::move(other.element);
            next = other.next;
            other.next = nullptr;
        }
        return *this;
    }

    ~Link() = default;
};

#endif // LINK_H
