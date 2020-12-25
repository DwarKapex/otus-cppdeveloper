#pragma once

#include <cstdlib>
#include <new>
#include <utility>

namespace Allocator {

//--------------------------------------
#pragma mark Allocator declaration
//--------------------------------------

template<typename T, size_t N>
class Allocator{
public:
    using value_type = T;
    using pointer = T*;
    Allocator();
    
    template<typename U>
    struct rebind;

    pointer allocate(std::size_t n = 1);
    void deallocate(pointer p, std::size_t n);
    template<typename U, typename ...Args>
    void construct(U *p, Args&&... args);
    void destroy(pointer p);

    ~Allocator();    

    bool operator==(const Allocator& other);
    bool operator!=(const Allocator& other);

private:
    T* FindAvailableChunk(std::size_t n);

    const size_t max_allocatable_objects;
    bool *m_free_chunks = nullptr;
    T *m_area = nullptr;
};

//--------------------------------------
#pragma mark Implementation
//--------------------------------------

template<typename T, size_t N>
Allocator<T, N>::Allocator(): max_allocatable_objects(N) {
    m_area = static_cast<T*> (::operator new (N*sizeof(T)));
    if (nullptr == m_area) {
        throw std::bad_alloc();
    }
    m_free_chunks = new bool[max_allocatable_objects];
    if (m_free_chunks == nullptr) {
        throw std::bad_alloc();
    }
    for (size_t i = 0; i < max_allocatable_objects; ++i) {
        m_free_chunks[i] = true;
    }
}
    
template<typename T, size_t N>    
template<typename U>
struct Allocator<T, N>::rebind{
     using other = Allocator<U, N>;
};

template<typename T, size_t N>
T* Allocator<T, N>::allocate(std::size_t n) { 
    if (n > max_allocatable_objects) 
        throw std::bad_alloc{};
    auto p = FindAvailableChunk(n); 
    return p;
}

template<typename T, size_t N>
void Allocator<T, N>::deallocate(T *p, std::size_t n) {
    int pos = (p-m_area);
    if (pos < 0 || pos + n > max_allocatable_objects)
         throw std::bad_alloc{};
    while (n >0) {
        m_free_chunks[pos] = false;
        ++pos;
        --n;
    }
}

template<typename T, size_t N>
template<typename U, typename ...Args>
void Allocator<T, N>::construct(U *p, Args&&... args) {
    new(p) U(std::forward<Args>(args)...);
}

template<typename T, size_t N>
void Allocator<T, N>::destroy(T *p) {
    p->~T();
}

template<typename T, size_t N>
Allocator<T, N>::~Allocator() {
    ::operator delete(m_area);
}

template<typename T, size_t N>
bool Allocator<T, N>::operator==(const Allocator& other) { 
    return true; 
}

template<typename T, size_t N>
bool Allocator<T, N>::operator!=(const Allocator& other) { 
    return !((*this)==other); 
}

template<typename T, size_t N>
T* Allocator<T, N>::FindAvailableChunk(std::size_t n) {
    size_t idx = 0;
    bool stop = false;
    while (!stop && idx + n < max_allocatable_objects) {
        while (!m_free_chunks[idx] && idx + n < max_allocatable_objects) {
            ++idx;
        }
        bool s = true;
        for (int i = 0; i < n; ++i) {
            s &= m_free_chunks[idx+i];
        }
        stop |= s;
    }
    if (idx+n > max_allocatable_objects)
        throw std::bad_alloc{};
    else{
        for (int i = 0; i < n; ++i){
            m_free_chunks[idx+i] = false;
        }
        return m_area + idx;
    }
}

} // namespace Allocator