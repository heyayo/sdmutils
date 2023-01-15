#ifndef SDMUTILS_MINHEAP_HPP
#define SDMUTILS_MINHEAP_HPP

#include <iostream>
#include "algorithm.hpp"

namespace sdm
{
    template<typename Type, int size>
    class minheap
    {
        Type* m_heap[size];
        int m_end;

        constexpr int left(int begin) const { return (begin*2)+1; }
        constexpr int right(int begin) const { return (begin*2)+2; }
        constexpr int parent(int begin) const { return (begin-1)/2; }

        constexpr void Preorder(int begin, std::ostream& stream, int tabCount) const
        {
            if (!m_heap[begin])
                return;
            ++tabCount;
            Type* leftchild = m_heap[left(begin)];
            Type* rightchild = m_heap[right(begin)];
            stream << *m_heap[begin] << std::endl;
            if (leftchild)
            {
                for (int i = 0; i < tabCount; ++i) stream << '\t';
                stream << "LEFT ";
                Preorder(left(begin), stream, tabCount);
            }
            if (rightchild)
            {
                for (int i = 0; i < tabCount; ++i) stream << '\t';
                stream << "RIGHT ";
                Preorder( right(begin), stream, tabCount);
            }
        }
        /* Find as if this was a linked list based min heap
        template<typename T, class compare>
        constexpr int Find(T target, compare comp, int begin)
        {
            if (!m_heap[begin])
                return -1;
            if (comp(target,m_heap[begin]))
                return begin;
            if (m_heap[(begin*2)+2]) // Left
                if (Find(target,comp,(begin*2)+2) != -1) return (begin*2)+2;
            if (m_heap[(begin*2)+1]) // Right
                return Find(target,comp,(begin*2)+1);
            return -1; // Fail Condition
        }
        constexpr int Find(Type* target, int begin = 0)
        {
            return Find(target,
                 [](Type* a, Type* b)
                 {
                return (*a == *b);
                 },begin);
        }
         * DuplicateCheck as if this was a linked list based min heap
        constexpr bool DuplicateCheck(Type* ref, int begin = 0)
        {
            if (m_heap[begin])
                return (*(m_heap[begin]) == *ref);
            if (m_heap[(begin*2)+2]) // Left
                if (DuplicateCheck(ref,(begin*2)+2)) return true;
            if (m_heap[(begin*2)+1]) // Right
                return DuplicateCheck(ref,(begin*2)+1);
            return false;
        }
         */
        constexpr bool DuplicateCheck(Type* ref)
        {
            for (int i = 0; i < m_end; ++i)
            {
                if (*ref == *m_heap[i]) return true;
            }
            return false;
        }
        constexpr void stablize(int begin = 0)
        {
            Type *leftChild = m_heap[left(begin)];
            Type *rightChild = m_heap[right(begin)];

            if (*leftChild < *m_heap[begin])
            {sdm::swap(leftChild,m_heap[begin]);
                stablize(left(begin));}
            if (*rightChild < *m_heap[begin])
            {sdm::swap(rightChild,m_heap[begin]);
                stablize(right(begin));}
        }
    public:
        minheap()
        {
            for (int i = 0; i < size; ++i)
                m_heap[i] = nullptr;
            m_end = -1;
        }
        ~minheap()
        {
            for (int i = 0; i < m_end; ++i)
                delete m_heap[i];
        }

        constexpr Type& operator[](const int& index) { return *m_heap[index]; }

        template<typename T, class comparator>
        constexpr int Find(T target, comparator comp)
        {
            Type* data;
            if constexpr (std::is_same<Type,T>::value)
                data = &target;
            else data = target;
            for (int i = 0; i < m_end; ++i)
            {
                if (comp(data,m_heap[i])) return i;
            }
            return -1;
        }
        template<typename T>
        constexpr int Find(T target)
        {
            Type* data;
            if constexpr (std::is_same<Type,T>::value)
                data = &target;
            else data = target;
            return Find(data,[](Type* a, Type* b){ return *a == *b; });
        }
        constexpr void insert(Type* payload)
        {
            if (m_end >= size) return;
            if (DuplicateCheck(payload)) return;
            m_heap[++m_end] = payload;

            int current = m_end;
            int parent = (current-1)/2;
            while ((*payload < *m_heap[parent]) && current > 0)
            {
                //if (!payload && !m_heap[parent]) break; if (!(*payload < *(m_heap[parent]))) break;
                /*
                Type* swap = m_heap[parent];
                m_heap[parent] = m_heap[current];
                m_heap[current] = swap;
                 */
                sdm::swap(m_heap[current],m_heap[parent]);

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
            if (position < 0) return;
            delete m_heap[position];
            m_heap[position] = nullptr;
            while (m_heap[++position])
            {
                m_heap[position-1] = m_heap[position];
            }
            m_heap[position-1] = nullptr;
            --m_end;
        }
        template<typename T>
        constexpr void remove(T payload)
        {
            Type* data;
            if constexpr (std::is_same<Type,T>::value)
                data = &payload;
            else data = payload;
            remove(data,[](Type* a, Type* b)
            {
                return *a == *b;
            });
        }
        constexpr void sort(int index)
        {
            int current = index;
            int parentIndex = parent(index);
            while ((*m_heap[current] < *m_heap[parentIndex]) && current > 0)
            {
                /*
                Type* swapptr = m_heap[current];
                m_heap[current] = m_heap[parentIndex];
                m_heap[parentIndex] = swapptr;
                 */
                sdm::swap(m_heap[current],m_heap[parentIndex]);

                current = parentIndex;
                parentIndex = parent(current);
            }
        }
        constexpr friend std::ostream& operator<<(std::ostream& stream, const minheap& heap) { heap.Preorder(0,stream, 0); return stream; }
        constexpr void debugPrint() { for (int i = 0; i < m_end+1; ++i) std::cout << *m_heap[i] << ", "; std::cout << std::endl;}
    };
}

#endif //SDMUTILS_MINHEAP_HPP
