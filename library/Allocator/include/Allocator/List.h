#pragma once

#include <memory>

namespace Allocator {

//------------------------------------------------------------
#pragma mark List Declaration
//------------------------------------------------------------

template <typename T, typename Allocator = std::allocator<T>>
class List
{
private:
    struct Node {
        T data = T();
        Node *next = nullptr;
    };

    using NodeAllocator = typename Allocator::template rebind<Node>::other;

public:
    struct iterator
    {
        Node* m_ptr;

        iterator(Node* ptr) : m_ptr(ptr) {}

        iterator operator++() { 
            m_ptr = m_ptr->next; 
        
        return *this; }
        T& operator*() { return m_ptr->data; }
        bool operator==(const iterator& rhs) { return m_ptr == rhs.m_ptr; }
        bool operator!=(const iterator& rhs) { return m_ptr != rhs.m_ptr; }
    };

    List();

    auto begin() -> iterator { return iterator(m_dummy_head->next); }
    auto end() -> iterator { return iterator(m_tail->next); }
    auto begin() const -> const iterator { return iterator(m_dummy_head->next); }
    auto end() const -> const iterator { return iterator(m_tail->next); }
    void push_back(const T &t);
    ~List();

private:
    Node *m_dummy_head = nullptr, *m_tail = nullptr;
    NodeAllocator m_node_allocator;
};

//------------------------------------------------------------
#pragma mark List Implementation
//------------------------------------------------------------

template <typename T, typename Allocator>
List<T, Allocator>::List(): m_dummy_head() {
    m_dummy_head = m_node_allocator.allocate(1);
    m_node_allocator.construct(m_dummy_head, Node{});
    m_tail = m_dummy_head;
}

template <typename T, typename Allocator>
void List<T, Allocator>::push_back(const T &t) {
    Node *node = m_node_allocator.allocate(1);
    m_node_allocator.construct(node, Node{t, nullptr});
    m_tail->next = node;
    m_tail = node;
}

template <typename T, typename Allocator>
List<T, Allocator>::~List()
{
    auto node = m_dummy_head->next;
    while (node != nullptr)
    {
        auto next_node = node->next;
        m_node_allocator.deallocate(node, 1);
        m_node_allocator.destroy(node);
        node = next_node;
    }
    m_node_allocator.deallocate(m_dummy_head, 1);
    m_node_allocator.destroy(m_dummy_head);
}

} // namespace slist