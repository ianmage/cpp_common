#pragma once

#include <functional>


struct PairHash
{
	template <typename T1, typename T2>
	std::size_t operator()(std::pair<T1,T2> const & p) {
		auto h1 = std::hash<T1>{}(p.first);
		auto h2 = std::hash<T2>{}(p.second);
		return h1 ^ h2;
	}
};
