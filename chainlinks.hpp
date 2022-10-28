#ifndef SDMUTILS_CHAINLINKS_HPP
#define SDMUTILS_CHAINLINKS_HPP

#include <iostream>

namespace sdm
{
    template<typename Type>
    class LinkedNode
    {
		public:
        using L = LinkedNode;
        using LRef = LinkedNode&;
        using LPtr = LinkedNode*;

		private:
        LinkedNode* m_Link;
        Type data;

        public:
        LinkedNode(Type payload) : data(payload), m_Link(nullptr) {}

        constexpr void Link(LPtr oLink)
        { m_Link = oLink; }
        inline LRef Traverse(int index)
        {
            LPtr temp = m_Link;
            for ( int i = 1; i < index; ++i )
            {
                temp = temp->GetLink();
            }
            return *temp;
        }
        constexpr bool IsEnd() { return m_Link == nullptr; }
		constexpr Type& Value() { return data; }
		constexpr LPtr Next() { return m_Link; }
        
        // Operator Overloads
        constexpr LRef operator++() { ++data; return *this; }
        constexpr LRef operator++(int) { data++; return *this; }
        constexpr LRef operator--() { ++data; return *this; }
        constexpr LRef operator--(int) { data++; return *this; }
        constexpr LRef operator+=(const LRef other) { data += other.data; return *this; }
        constexpr LRef operator-=(const LRef other) { data -= other.data; return *this; }
        constexpr L operator+(const LRef other) { L temp = *this; return temp += other; }
        constexpr L operator-(const LRef other) { L temp = *this; return temp -= other; }
        constexpr LRef operator*() { return data; }
        constexpr LPtr operator->() { return &data; }
        constexpr bool operator==(const LRef other) { return data == other.data; }
        constexpr bool operator!=(const LRef other) { return data != other.data; }
        constexpr bool operator<(const LRef other) { return data < other.data; }
        constexpr bool operator>(const LRef other) { return data > other.data; }
        constexpr bool operator>=(const LRef other) { return data >= other.data; }
        constexpr bool operator<=(const LRef other) { return data <= other.data; }
        constexpr friend std::ostream& operator<<(std::ostream& stream, const LRef other)
        { stream << other.data; return stream; }
    };

	template<class LinkedNode>
	class LinkedListIterator
	{
		public:
		using Type = LinkedNode;
		using TypeRef = LinkedNode&;
		using TypePtr = LinkedNode*;
		using Iter = LinkedListIterator;
		using IterRef = Iter&;
		using IterPtr = Iter*;

		TypePtr m_Ptr;

		public:
		LinkedListIterator(TypePtr to) : m_Ptr(to) {}

		constexpr IterRef operator++()
		{ m_Ptr = m_Ptr->Next(); return *this; }
		constexpr IterRef operator++(int)
		{ auto temp = *this; ++(*this); return temp; }
		constexpr IterRef operator+=(const int diff)
		{ m_Ptr += diff; return *this; }
		constexpr Iter operator+(const int diff)
		{ auto temp = *this; return temp += diff; }
		constexpr TypeRef operator*()
		{ return *m_Ptr; }
		constexpr TypePtr operator->()
		{ return m_Ptr; }
		constexpr bool operator==(IterRef other) const
		{ return m_Ptr == other.m_Ptr; }
		constexpr bool operator!=(IterRef other) const
		{ return m_Ptr != other.m_Ptr; }
	};

	template<typename Type>
	class LinkedList
	{
		public:
		using TypeRef = Type&;
		using TypePtr = Type*;
		using Node = LinkedNode<Type>;
		using NodeRef = Node&;
		using NodePtr = Node*;
		using Iter = LinkedListIterator<LinkedNode<Type>>;
		using IterRef = Iter&;
		using IterPtr = Iter*;

		LinkedList(Type first)
		{
			m_HEAD = new Node(first);
			m_TAIL = m_HEAD;
			m_Capacity = 1;
		}
		// TODO DECONSTRUCTOR

		private:
		NodePtr m_HEAD;
		NodePtr m_TAIL;
		unsigned m_Capacity;

		public:
		constexpr NodePtr first()
		{ return m_HEAD; }
		constexpr NodePtr last()
		{ return m_TAIL; }
		constexpr unsigned capacity()
		{ return m_Capacity;}
		constexpr Iter begin()
		{ return Iter(m_HEAD); }
		constexpr Iter end()
		{ return Iter(m_TAIL); }

		constexpr NodeRef operator[](const int index)
		{
			auto temp = m_HEAD;
			for ( int i = 0; i < index; ++i )
			{ temp = temp->Next(); }
			return *temp;
		}

		constexpr void chainback(Type data)
		{
			NodePtr temp = new Node(data);
			m_TAIL->Link(temp);
			m_TAIL = temp;
			++m_Capacity;
		}
		constexpr void chainfront(Type data)
		{
			NodePtr temp = new Node(data);
			temp->Link(m_HEAD);
			m_HEAD = temp;
			++m_Capacity;
		}

		constexpr friend std::ostream& operator<<(std::ostream& stream, LinkedList& other)
		{
			for (int i = 0; i < other.capacity(); ++i)
			{
				stream << other[i] << ' ';
			}

			return stream;
		}
	};
}

#endif
