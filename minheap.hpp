#ifndef SDMUTILS_MINHEAP_HPP
#define SDMUTILS_MINHEAP_HPP

#include <iostream>

namespace sdm
{
    template<typename Type, size_t size>
    class minheap
    {
        Type* m_heap[size];
        size_t m_end;

        constexpr size_t left(size_t begin) const { return (begin*2)+2; }
        constexpr size_t right(size_t begin) const { return (begin*2)+1; }
        constexpr size_t parent(size_t begin) const { return (begin-1)/2; }

        constexpr void Preorder(size_t begin, std::ostream& stream) const
        {
            if (!m_heap[begin])
                return;
            Type* leftchild = m_heap[left(begin)];
            Type* rightchild = m_heap[right(begin)];
            stream << "NODE " << *m_heap[begin] << std::endl;
            if (leftchild)
                stream << "LEFT CHILD: " << *leftchild << std::endl;
            else stream << "NIL" << std::endl;
            if (rightchild)
                stream << "RIGHT CHILD: " << *rightchild << std::endl;
            else stream << "NIL" << std::endl;
            stream << std::endl;
            Preorder(left(begin), stream);
            Preorder( right(begin), stream);
        }
        template<typename T, class compare>
        constexpr int Find(T target, compare comp, size_t begin = 0)
        {
            if (!m_heap[begin])
                return -1;
            if (comp(target,m_heap[begin]))
                return begin;
            if (m_heap[left(begin)])
                if (Find(target,left(begin)) != -1) return left(begin);
            if (m_heap[right(begin)])
                return Find(target,right(begin));
            return -1; // Fail Condition
        }
        constexpr int Find(Type* target, size_t begin = 0)
        {
            return Find(target,
                 [](Type* a, Type* b)
                 {
                return (*a == *b);
                 },begin);
        }
        constexpr bool DuplicateCheck(Type* ref, size_t begin = 0)
        {
            if (m_heap[begin])
                if (*(m_heap[begin]) == *ref) return true;
            if (m_heap[left(begin)])
                if (DuplicateCheck(ref,left(begin))) return true;
            if (m_heap[right(begin)])
                return DuplicateCheck(ref,right(begin));
            return false;
        }

    public:
        minheap()
        {
            for (size_t i = 0; i < size; ++i)
                m_heap[i] = nullptr;
            m_end = -1;
        }
        ~minheap()
        {
            for (size_t i = 0; i < m_end; ++i)
                delete m_heap[i];
        }

        constexpr void insert(Type* payload)
        {
            if (m_end == size) return;
            if (DuplicateCheck(payload)) return;
            m_heap[++m_end] = payload;

            size_t current = m_end;
            size_t parent = (current-1)/2;
            while ((*payload < *m_heap[parent]) && current > 0)
            {
                Type* swap = m_heap[parent];
                m_heap[parent] = m_heap[current];
                m_heap[current] = swap;

                current = parent;
                parent = (current-1)/2;
            }
        }
        template<typename T, class compare>
        constexpr void remove(T payload, compare comparator)
        {
            int position;
            if constexpr (std::is_same<Type,T>::value)
                position = Find(&payload,comparator);
            else position = Find(payload,comparator);
            delete m_heap[position];
            m_heap[position] = nullptr;
            while (m_heap[++position])
            {
                m_heap[position-1] = m_heap[position];
            }
            m_heap[position-1] = nullptr;
            --m_end;
        }
        constexpr void remove(Type* payload)
        {
            remove(payload,[](Type* a, Type* b)
            {
                return a == b;
            });
        }
        constexpr friend std::ostream& operator<<(std::ostream& stream, const minheap& heap) { heap.Preorder(0,stream); return stream; }
        constexpr void debugPrint() { for (size_t i = 0; i < m_end+1; ++i) std::cout << *m_heap[i] << ", "; std::cout << std::endl;}
    };
}

#endif //SDMUTILS_MINHEAP_HPP
