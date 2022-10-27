#ifndef SDMUTILS_CHAINLINKS_HPP
#define SDMUTILS_CHAINLINKS_HPP

#include <iostream>

namespace sdm
{
	// DEPRECIATED
    template<class NodeType>
    class LNodeControl
    {
        public:
        using LNC = LNodeControl;
        using LRef = LNC&;
        using LPtr = LNC*;

        NodeType* m_HEAD = nullptr;
        NodeType* m_TAIL = nullptr;
        int m_Length = 1;

        constexpr LRef operator+=(const LRef other)
        { m_Length += other.m_Length; m_TAIL = other.m_TAIL; return *this; }
        constexpr LRef operator-=(const LRef other)
        { m_Length -= other.m_Length; }
    };

    template<typename Type>
    class LinkedNode
    {
        public:
        using L = LinkedNode;
        using LRef = LinkedNode&;
        using LPtr = LinkedNode*;

        LinkedNode* m_Link = nullptr;

        LinkedNode<LinkedNode>(Type payload) : data(payload) {}

        inline void Link(LinkedNode* oLink)
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
        inline bool IsEnd() { return m_Link == nullptr; }
        
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
        
        Type data;
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

		LinkedList<Type>(Type first)
		{
			m_HEAD = new Node(first);
			m_TAIL = m_HEAD;
			capacity = 1;
		}
		// TODO DECONSTRUCTOR

		private:
		NodePtr m_HEAD;
		NodePtr m_TAIL;
		unsigned capacity;

		public:
		constexpr NodePtr first()
		{ return m_HEAD; }
		constexpr NodePtr last()
		{ return m_TAIL; }

		constexpr void chainback(Type data)
		{
			auto temp = new Node(data);
			m_TAIL->m_Link = temp;
			m_TAIL = temp;
			++capacity;
		}
		constexpr void chainfront(Type data)
		{
			auto temp = new Node(data);
			temp->m_Link = m_HEAD;
			m_HEAD = temp;
			++capacity;
		}

		constexpr friend std::ostream& operator<<(std::ostream& stream, LinkedList& other)
		{
			auto curr = other.first();
			while (curr->m_Link != nullptr)
			{
				stream << curr->data << ' ';
			}
			return stream;
		}
	};
}

#endif
