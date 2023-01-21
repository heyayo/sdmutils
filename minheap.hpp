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
				if (!m_heap[i]) continue;
                if (*ref == *m_heap[i]) return true;
            }
            return false;
        }
		constexpr void upsort(int index)
		{
			int parentIndex = parent(index);
			while ((*m_heap[index] < *m_heap[parentIndex]) && index > 0)
			{
				sdm::swap(m_heap[index],m_heap[parentIndex]);
				index = parentIndex;
				parentIndex = parent(index);
			}
		}
		constexpr void downsort(int index)
		{
			int leftChildIndex = left(index);
			int rightChildIndex = right(index);
			while (index < m_end)
			{
				bool leftGood = m_heap[leftChildIndex] != nullptr;
				bool rightGood = m_heap[rightChildIndex] != nullptr;
				if (leftGood && rightGood)
				{
					if (*m_heap[leftChildIndex] < *m_heap[rightChildIndex])
					{
						if (*m_heap[leftChildIndex] < *m_heap[index])
						{
							sdm::swap(m_heap[leftChildIndex], m_heap[index]);
							index = leftChildIndex;
							leftChildIndex = left(index);
							rightChildIndex = right(index);
							continue;
						}
					}
					else
					{
						if (*m_heap[rightChildIndex] < *m_heap[index])
						{
							sdm::swap(m_heap[rightChildIndex],m_heap[index]);
							index = rightChildIndex;
							leftChildIndex = left(index);
							rightChildIndex = right(index);
							continue;
						}
					}
				}
				if (leftGood)
				{
					if (*m_heap[leftChildIndex] < *m_heap[index])
					{
						sdm::swap(m_heap[leftChildIndex],m_heap[index]);
						index = leftChildIndex;
						leftChildIndex = left(index);
						rightChildIndex = right(index);
						continue;
					}
				}
				if (rightGood)
				{
					if (*m_heap[rightChildIndex] < *m_heap[index])
					{
						sdm::swap(m_heap[rightChildIndex],m_heap[index]);
						index = rightChildIndex;
						leftChildIndex = left(index);
						rightChildIndex = right(index);
						continue;
					}
				}
				break;
			}
		}
        /* Forces value at index to root position, unused
		constexpr void forceup(int index)
		{
			int parentIndex = parent(index);
			while (index > 0)
			{
				sdm::swap(m_heap[index],m_heap[parentIndex]);
				index = parentIndex;
				parentIndex = parent(index);
			}
		}
        */
		constexpr void forcedown(int index)
		{
			int leftChild = left(index);
			int rightChild = right(index);
			while (index < m_end)
			{
				bool leftGood = m_heap[leftChild] != nullptr;
				bool rightGood = m_heap[rightChild] != nullptr;
				if (leftGood && rightGood)
				{
					if (*m_heap[leftChild] < *m_heap[rightChild])
					{
						sdm::swap(m_heap[index],m_heap[leftChild]);
						index = leftChild;
						leftChild = left(index);
						rightChild = right(index);
						continue;
					} else
					{
						sdm::swap(m_heap[index], m_heap[rightChild]);
						index = rightChild;
						leftChild = left(index);
						rightChild = right(index);
						continue;
					}
				}
				if (leftGood)
				{
					sdm::swap(m_heap[index],m_heap[leftChild]);
					index = leftChild;
					leftChild = left(index);
					rightChild = right(index);
					continue;
				}
				if (rightGood)
				{
					sdm::swap(m_heap[index],m_heap[rightChild]);
					index = rightChild;
					leftChild = left(index);
					rightChild = right(index);
					continue;
				}
				break;
			}
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
                if (!m_heap[i]) continue;
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
		constexpr void stabilize(int index)
		{
			upsort(index);
			downsort(index);
		}
        constexpr void insert(Type* payload)
        {
            if (m_end >= size) return;
            if (DuplicateCheck(payload)) return;
            m_heap[++m_end] = payload;

            int current = m_end;
            int parent = (current-1)/2;
            while (m_heap[parent] && current > 0)
            {
				if (!(*payload < *m_heap[parent])) break;
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
            int position = -1;
            if constexpr (std::is_same<Type,T>::value)
                position = Find(&payload,comparator);
            else position = Find(payload,comparator);
            if (position < 0) return;
			// forceup(position);
            delete m_heap[position];
            m_heap[position] = nullptr;
			forcedown(position);
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
        constexpr friend std::ostream& operator<<(std::ostream& stream, const minheap& heap) { heap.Preorder(0,stream, 0); return stream; }
        constexpr void debugPrint()
		{
			for (int i = 0; i < m_end+1; ++i)
			{
				if (!m_heap[i])
				{
					std::cout << "NULL ";
					continue;
				}
				std::cout << *m_heap[i] << ", ";
			}
			std::cout << std::endl;
		}
    };
}

#endif //SDMUTILS_MINHEAP_HPP
