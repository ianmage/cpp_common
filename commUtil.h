#pragma once

#define PRIME_NUM 0x9e3779b9


constexpr size_t _Hash(char const * str, size_t seed)
{
	return 0 == *str ? seed : _Hash(str + 1, seed ^ (*str + PRIME_NUM + (seed << 6) + (seed >> 2)));
}

#ifdef _MSC_VER
template <size_t N>
struct EnsureConst
{
	static const size_t value = N;
};

#define CT_HASH(x) (EnsureConst<_Hash(x, 0)>::value)
#else
#define CT_HASH(x) (_Hash(x, 0))
#endif


template <typename SizeT>
inline void HashCombineImpl(SizeT& seed, SizeT value)
{
	seed ^= value + PRIME_NUM + (seed << 6) + (seed >> 2);
}

inline size_t RT_HASH(char const * str)
{
	size_t seed = 0;
	while (*str != 0)
	{
		HashCombineImpl(seed, static_cast<size_t>(*str));
		++str;
	}
	return seed;
}

#undef PRIME_NUM

template <typename T>
inline size_t HashValue(T v)
{
	return static_cast<size_t>(v);
}

template <typename T>
inline size_t HashValue(T* v)
{
	return static_cast<size_t>(reinterpret_cast<ptrdiff_t>(v));
}

template <typename T>
inline void HashCombine(size_t& seed, T const & v)
{
	return HashCombineImpl(seed, HashValue(v));
}

template <typename T>
inline void HashRange(size_t& seed, T first, T const & last)
{
	for (; first != last; ++first)
	{
		HashCombine(seed, *first);
	}
}

template <typename T>
inline size_t HashRange(T first, T const & last)
{
	size_t seed = 0;
	HashRange(seed, first, last);
	return seed;
}


template <typename T = char, typename U>
inline size_t HashObj(U const & pObj)
{
	T const * myBegin = reinterpret_cast<T const *>(&pObj);
	T const * myEnd = myBegin + sizeof(U);

	return HashRange(myBegin, myEnd);
}


#define ArrayCount(x)	sizeof(x)/sizeof((x)[0])
