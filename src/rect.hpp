#pragma once

#include <algorithm>
#include <glm/glm.hpp>

template <typename T>
struct Rect
{
	constexpr Rect();
	constexpr Rect(T pos, T size);

	template <typename U>
	explicit Rect(const Rect<U> &rectangle);

	constexpr Rect& operator/=(const T &divider);

	bool contains(T point) const;
	bool intersect(const Rect<T> &other);

	T pos;
	T size;
};

typedef Rect<glm::vec2> FloatRect;
typedef Rect<glm::ivec2> IntRect;

template <typename T>
constexpr
Rect<T>::Rect()
	: pos()
	, size()
{
}

template <typename T>
constexpr
Rect<T>::Rect(T pos, T size)
	: pos(pos)
	, size(size)
{
}

template <typename T>
template <typename U>
Rect<T>::Rect(const Rect<U> &other)
	: pos(static_cast<T>(other.pos))
	, size(static_cast<T>(other.size))
{
}

template <typename T>
constexpr Rect<T> &
Rect<T>::operator/=(const T &divider)
{
	pos /= divider;
	size /= divider;
	return *this;
}

template <typename T>
constexpr Rect<T>
operator/(const Rect<T> &dividend, const T &divisor)
{
	return { dividend.pos / divisor, dividend.size / divisor };
}

template <typename T>
bool
Rect<T>::contains(T point) const
{
	return pos.x <= point.x && point.x < pos.x + size.x
		&& pos.y <= point.y && point.y < pos.y + size.y;
}

template <typename T>
bool
Rect<T>::intersect(const Rect<T> &other)
{
	return pos.x < other.pos.x + other.size.x
		&& pos.x + size.x > other.pos.x
		&& pos.y < other.pos.y + other.size.y
		&& pos.y + size.y > other.pos.y;
}

template <typename T>
constexpr bool
operator==(const Rect<T> &lhs, const Rect<T> &rhs)
{
	return lhs.pos.x == rhs.pos.x
		&& lhs.pos.y == rhs.pos.y
		&& lhs.size.x == rhs.size.x
		&& lhs.size.y == rhs.size.y;
}

template <typename T>
constexpr bool
operator!=(const Rect<T> &lhs, const Rect<T> &rhs)
{
	return !(lhs == rhs);
}
