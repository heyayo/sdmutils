#ifndef SDMUTILS_CHAINLINKS_HPP
#define SDMUTILS_CHAINLINKS_HPP

namespace sdm
{
    template<class NodeType>
    class LNodeControl
    {
        public:
        using LNC = LNodeControl;
        using LRef = LNC&;
        using LPtr = LNC*;

        NodeType m_HEAD = nullptr;
        NodeType m_TAIL = nullptr;
        size_t m_Length = 1;

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
        LNodeControl* m_Control = nullptr

        LinkedNode(Type payload) : data(payload) { m_Control = new LNodeControl{this, this}; }

        inline void Link(LinkedNode* oLink)
        { m_Link = oLink; delete oLink.m_Control; oLink.m_Control = m_Control; }
        inline LRef Traverse(size_t index)
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
}

#endif