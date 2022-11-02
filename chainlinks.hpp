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
    class BaseNode
    {
		public:
        using N = BaseNode;
        using NRef = N&;
        using NPtr = N*;

		protected:
        Type data;
		BaseNode(Type payload) : data(payload) { std::cout << "DEBUG BASENODE" << std::endl; }
		~BaseNode() { std::cout << "DEBUG BASENODE DEATH" << std::endl; }

        public:
		constexpr Type& value() { return data; }

        // Operator Overloads
        constexpr NRef operator++() { ++data; return *this; }
        constexpr N operator++(int) { N temp = *this; ++data; return temp; }
        constexpr NRef operator--() { --data; return *this; }
        constexpr N operator--(int) { N temp = *this; --data; return temp; }
        constexpr NRef operator+=(const NRef other) { data += other.data; return *this; }
        constexpr NRef operator-=(const NRef other) { data -= other.data; return *this; }
        constexpr N operator+(const NRef other) { N temp = *this; return temp += other; }
        constexpr N operator-(const NRef other) { N temp = *this; return temp -= other; }
        constexpr NRef operator*() { return *this; }
        constexpr NPtr operator->() { return this; }
        constexpr bool operator==(const NRef other) { return data == other.data; }
        constexpr bool operator!=(const NRef other) { return data != other.data; }
        constexpr bool operator<(const NRef other) { return data < other.data; }
        constexpr bool operator>(const NRef other) { return data > other.data; }
        constexpr bool operator>=(const NRef other) { return data >= other.data; }
        constexpr bool operator<=(const NRef other) { return data <= other.data; }
        //constexpr friend std::ostream& operator<<(std::ostream& stream, const LRef other)
        //{ stream << other.data; return stream; }
    };

	/*
	template<typename Type>
	class FNode : virtual public BaseNode<Type>
	{
		public:
		using N = FNode<Type>;
		using NRef = N&;
		using NPtr = N*;

		protected:
		NPtr m_Forward;

		public:
        FNode(Type payload) : BaseNode<Type>(payload), m_Forward(nullptr) { std::cout << "DEBUG FNODE" << std::endl; }

        constexpr void linkFront(NPtr oLink)
        { m_Forward = oLink; }
        constexpr bool isHead() { return m_Forward == nullptr; }
		constexpr NPtr prev() { return m_Forward; }
	};
	Same as BNode except worse
	*/ 

	template<typename Type>
	class BNode : public BaseNode<Type>
	{
		public:
		using N = BNode<Type>;
		using NRef = N&;
		using NPtr = N*;

		protected:
		NPtr m_Backward;

		public:
		BNode(Type payload) : BaseNode<Type>(payload), m_Backward(nullptr) { std::cout << "DEBUG BNODE" << std::endl; }
		~BNode() { std::cout << "DEBUG BNODE DEATH" << std::endl; }

		constexpr void linkBack(NPtr oLink)
		{ m_Backward = oLink; }
		constexpr bool isTail() { return m_Backward == nullptr; }
		constexpr NPtr next() { return m_Backward; }
	};

	template<typename Type>
	class DNode : public BaseNode<Type>
	{
		public:
		using N = DNode<Type>;
		using NRef = N&;
		using NPtr = N*;

		private:
		NPtr m_Forward;
		NPtr m_Backward;

		public:
		DNode(Type payload) : BaseNode<Type>(payload), m_Forward(nullptr), m_Backward(nullptr)
		{ std::cout << "DEBUG DNODE" << std::endl; }
		DNode() { std::cout << "DEBUG DNODE DEATH" << std::endl; }

		constexpr void linkBack(NPtr oLink) { m_Backward = oLink; }
		constexpr void linkFront(NPtr oLink) { m_Forward = oLink; }
		constexpr bool isHead() { return m_Forward == nullptr; }
		constexpr bool isTail() { return m_Backward == nullptr; }
		constexpr NPtr next() { return m_Backward; }
		constexpr NPtr prev() { return m_Forward; }
	};

	/* Depreciated In Favor of DNode
	template<typename Type>
	class DualLinkedNode : public LinkedNode<Type>
	{
		using L = DualLinkedNode;
		using LRef = L&;
		using LPtr = L*;

		LPtr m_Backward;

		public:
		DualLinkedNode(Type payload) : LinkedNode<Type>(payload), m_Backward(nullptr) {}

		constexpr void LinkBack(LPtr oLink)
		{ m_Backward = oLink; }
		constexpr LPtr Back() { return m_Backward; }
		constexpr bool IsHead() { return m_Backward == nullptr; }

	};
	*/

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

	template<template<typename> class NodeType, typename Type>
	class LinkedList
	{
		public:
		using Node = NodeType<Type>;
		using NodeRef = Node&;
		using NodePtr = Node*;
		using Iter = LinkedListIterator<Node>;
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
		~LinkedList()
		{
			auto next = m_HEAD;
			auto curr = m_HEAD;
			m_HEAD = nullptr;
			m_TAIL = nullptr;
			for (int i = 1; i < m_Capacity; ++i)
			{
				next = curr->next();
				delete curr;
				curr = next;
			}
			delete curr;
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
			{ temp = temp->next(); }
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
				if constexpr (std::is_same<BNode<Type>,Node>::value)
				{
					m_TAIL->linkBack(temp);
					temp->linkBack(nullptr);
					m_TAIL = temp;
				}
				if constexpr (std::is_same<DNode<Type>,Node>::value)
				{
					m_TAIL->linkBack(temp);
					temp->linkFront(m_TAIL);
					temp->linkBack(nullptr);
					m_TAIL = temp;
				}
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
				if constexpr (std::is_same<BNode<Type>,Node>::value)
				{
					temp->linkBack(m_HEAD);
					m_HEAD = temp;
				}
				if constexpr (std::is_same<DNode<Type>,Node>::value)
				{
					m_HEAD->linkFront(temp);
					temp->linkBack(m_HEAD);
					temp->linkFront(nullptr);
					m_HEAD = temp;
				}
			}
			++m_Capacity; // Increase capacity
		}
		constexpr Type detach(int index) // Detach Node and return
		{
			--m_Capacity; // Decrease capacity
			if (index == 0)
			{
				if constexpr (std::is_same<BNode<Type>,Node>::value || std::is_same<DNode<Type>,Node>::value)
				{
					auto temp = m_HEAD;
					m_HEAD = m_HEAD->next();
					if constexpr (std::is_same<DNode<Type>,Node>::value)
					{
						m_HEAD->linkFront(nullptr);
					}
					Type returnval = temp->value();
					delete temp;
					return returnval;
				}
			}
			if constexpr (std::is_same<BNode<Type>,Node>::value || std::is_same<DNode<Type>,Node>::value)
			{
				auto prev = m_HEAD; // The node behind
				for (int i = 1; i < index; ++i)
				{
					prev = prev->next(); // Going to the node behind
				}
				auto curr = prev->next(); // Going to the node to delete
				if (curr->isTail()) // If deleting last node
				{ 
					m_TAIL = prev; // Set tail to behind
					prev->linkBack(nullptr); // Make node point to nullptr
				} 
				else // If not deleting last node
				{
					prev->linkBack(curr->next()); // Detach node from links and relink behind and after
					if constexpr (std::is_same<DNode<Type>,Node>::value)
					{
						curr->next()->linkFront(prev);
					}
				}
				Type returnval = curr->value(); // Save return value
				delete curr; // Delete node
				return returnval;
			}
		}

		constexpr friend std::ostream& operator<<(std::ostream& stream, LinkedList& other)
		{
			auto curr = other.first();
			while (!curr->isTail())
			{
				stream << curr->value() << ',';
				curr = curr->next();
			}
			stream << curr->value();
			return stream;
		}
		/*
		constexpr friend std::ostream& operator<<(std::ostream& stream, NodeRef other)
		{
			auto curr = other.first();
			while (!curr->isTail())
			{
				stream << curr->value() << ' ';
				curr = curr->next();
			}
			stream << curr->value() << ' ';
			return stream;
		}
		*/
	};

	/* Unused In Favor of more templates
	template<typename Type>
	class DualLinkedList : public LinkedList<Type>
	{
		public:
		using Node = DualLinkedNode<Type>;
		using NodeRef = Node&;
		using NodePtr = Node*;

		private:
		NodePtr m_HEAD;
		NodePtr m_TAIL;
		int m_Capacity;

		public:
		DualLinkedList(Type first) : LinkedList<Type>(first) {}
		
	};
	*/
}

#endif
