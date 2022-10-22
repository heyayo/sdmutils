#ifndef SDMUTILS_CHAINLINKS_HPP
#define SDMUTILS_CHAINLINKS_HPP

namespace sdm
{
    template<typename Type>
    class LinkedNode
    {
        using L = LinkedNode;
        using LRef = LinkedNode&;
        using LPtr = LinkedNode*;

        LinkedNode* mLink = nullptr;

        public:
        LinkedNode(Type payload) : data(payload) {}

        inline void Link(LinkedNode* oLink) { mLink = oLink; }
        inline LPtr GetLink() { return mLink; }
        inline LRef Traverse(size_t index)
        {
            LPtr temp = mLink;
            for ( int i = 1; i < index; ++i )
            {
                temp = temp->GetLink();
            }
            return *temp;
        }
        inline bool IsEnd() { return mLink == nullptr; }
        
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