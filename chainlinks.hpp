#ifndef SDMUTILS_CHAINLINKS_HPP
#define SDMUTILS_CHAINLINKS_HPP

/*
*  SDMUTILS
*  An Attempt to Recreate Things from STL and more
* 
*  CHAINLINKS Includes
*  LinkedList
*  LinkedNode
*  LinkedListIterator W.I.P unsafe
*/

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
        inline LRef Traverse(int index) // unsafe
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
	class LinkedListIterator // W.I.P
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
		LinkedList()
		{
			m_HEAD = nullptr;
			m_TAIL = nullptr;
			m_Capacity = 0;
		}
		// TODO DECONSTRUCTOR
		~LinkedList()
		{
			auto next = m_HEAD;
			auto curr = m_HEAD;
			for (int i = 0; i < m_Capacity; ++i)
			{
				next = curr->Next();
				delete curr;
				curr = next;
			}
		}

		private:
		NodePtr m_HEAD;
		NodePtr m_TAIL;
		int m_Capacity;

		public:
		constexpr NodePtr first()
		{ return m_HEAD; }
		constexpr NodePtr last()
		{ return m_TAIL; }
		constexpr int capacity()
		{ return m_Capacity;}
		constexpr Iter begin()
		{ return Iter(m_HEAD); }
		constexpr Iter end()
		{ return Iter(m_TAIL); }
		constexpr bool isEmpty()
		{ return m_Capacity <= 0; }

		constexpr NodeRef operator[](const int index)
		{
			auto temp = m_HEAD;
			for ( int i = 0; i < index; ++i )
			{ temp = temp->Next(); }
			return *temp;
		}

		constexpr void chainback(Type data) // Add node from Tail End
		{
			NodePtr temp = new Node(data); // new node
			if (isEmpty())
			{
				m_HEAD = temp; // Initialize HEAD
				m_TAIL = temp; // Initialize TAIL
			}
			else
			{
				m_TAIL->Link(temp); // Link new node as new tail
				m_TAIL = temp; // Reset tail to new node
			}
			++m_Capacity; // Increase capacity
		}
		constexpr void chainfront(Type data) // Add node from Head End
		{
			NodePtr temp = new Node(data); // new node
			if (isEmpty())
			{
				m_HEAD = temp; // Initialize HEAD
				m_TAIL = temp; // Initialize TAIL
			}
			else
			{
				temp->Link(m_HEAD); // Link new node as new head
				m_HEAD = temp; // Reset head to new node
			}
			++m_Capacity; // Increase capacity
		}
		constexpr Type detach(int index) // Detach Node and return
		{
			--m_Capacity; // Decrease capacity
			if (index == 0)
			{
				auto temp = m_HEAD;
				m_HEAD = m_HEAD->Next();
				Type returnval = temp->Value();
				delete temp;
				return returnval;
			}
			auto prev = m_HEAD;; // The node behind
			for (int i = 1; i < index; ++i)
			{
				prev = prev->Next(); // Going to the node behind
			}
			auto curr = prev->Next(); // Going to the node to delete
			if (curr->IsEnd()) // If deleting last node
			{
				m_TAIL = prev; // Set tail to behind
				prev->Link(nullptr); // Make node point to nullptr
			}
			else // If not deleting last node
				prev->Link(curr->Next()); // Detach node from links and relink behind and after
			Type returnval = curr->Value(); // Save return value
			delete curr; // Delete node
			return returnval;
		}

		constexpr friend std::ostream& operator<<(std::ostream& stream, LinkedList& other)
		{
			auto curr = other.first();
			while (!curr->IsEnd())
			{
				stream << curr->Value() << ' ';
				curr = curr->Next();
			}
			stream << curr->Value() << ' ';
			return stream;
		}
	};
}

#endif
