#ifndef SDMUTILS_V3_HPP
#define SDMUTILS_V3_HPP
#include "math.hpp"
#include "exceptions.hpp"
#include <iostream>

namespace sdm
{
struct V3
{
	float x = 0,y = 0,z = 0;

	constexpr V3& operator+=(const V3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	constexpr V3 operator+(const V3& other) const
	{ auto temp = *this; return temp+=other; }
	constexpr V3& operator-=(const V3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	constexpr V3 operator-(const V3& other) const
	{ auto temp = *this; return temp-=other; }
	constexpr V3& operator*=(const int& other)
	{
		x *= other;
		y *= other;
		z *= other;
		return *this;
	}
	constexpr V3 operator*(const int other) const
	{ auto temp = *this; return temp*=other; }

	constexpr bool operator==(const V3& other) const
	{return
		fEqual(x,other.x) && fEqual(y,other.y) && fEqual(z,other.z);}
	constexpr bool operator!=(const V3& other) const
	{return
		!(*this == other);}
	constexpr V3& operator=(const V3& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
	constexpr V3 operator-()
	{return {-x,-y,-z};}

	friend std::ostream& operator<<(std::ostream& stream, const V3& other)
	{ stream << other.x << ',' << other.y << ',' << other.z; return stream; }
	
	constexpr float dot(const V3& other) const
	{
		auto temp = *this;
		temp.x *= other.x;
		temp.y *= other.y;
		temp.z *= other.z;

		return temp.x + temp.y + temp.z;
	}
	constexpr V3 cross(const V3& other) const
	{
		auto reefer = *this;
		V3 left{};
		V3 right{};
		left.x = reefer.y * other.z;
		right.x = reefer.z * other.y;
		
		left.y = reefer.z * other.x;
		right.y = reefer.x * other.z;

		left.z = reefer.x * other.y;
		right.z = reefer.y * other.x;

		return {
			left.x - right.x,
			left.y - right.y,
			left.z - right.z
		};
	}
	constexpr float lengthSquared() const
	{
		auto tempv = *this;
		float temp =
			tempv.x*tempv.x +
			tempv.y*tempv.y +
			tempv.z*tempv.z;
		return temp;
	}
	constexpr float length() const
	{
		return root(lengthSquared());
	}
	constexpr float distance(const V3& other)
	{return (*this - other).length();}
	constexpr float distanceSquared(const V3& other)
	{return (*this - other).lengthSquared();}
	constexpr bool IsZero()
	{return
		fEqual(x,0.f), fEqual(y,0.f), fEqual(z,0.f); }
	constexpr V3 normalized() const throw(DivideByZero)
	{
		float d = length();
		if (d <= sdm::EPSILON && -d <= sdm::EPSILON)
		{
			throw DivideByZero();
		}
		return {x / d, y / d, z / y};
	}
};
}
#endif
