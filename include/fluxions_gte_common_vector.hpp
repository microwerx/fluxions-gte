#ifndef FLUXIONS_GTE_COMMON_VECTOR_HPP
#define FLUXIONS_GTE_COMMON_VECTOR_HPP

namespace Fluxions
{
	template <typename T>
	class TCommonContainer {
	public:
		static constexpr T zero = T(0);
		static constexpr T one = T(1);
		static constexpr T minusone = T(-1);
		static constexpr bool is_signed = T(-1) < 0;
	};

	template <typename T>
	class TCommonIterator {
	public:
		TCommonIterator(T* ptr) : ptr(ptr) {}
		TCommonIterator operator++() { ++ptr; return *this; }
		bool operator !=(const TCommonIterator& other) const { return ptr != other.ptr; }
		const T& operator*() const { return *ptr; }
		T& operator*() { return *ptr; }
	private:
		T* ptr;
	};
}
#endif
