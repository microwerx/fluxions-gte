#ifndef FLUXIONS_GTE_VECTOR_MATH_HPP
#define FLUXIONS_GTE_VECTOR_MATH_HPP

#include <fluxions_gte_scalar_math.hpp>
#include <fluxions_gte_vector2.hpp>
#include <fluxions_gte_vector3.hpp>
#include <fluxions_gte_vector4.hpp>
#include <fluxions_gte_quaternion.hpp>

// This header defines math between scalars and vector types
// * scalars and vectors
// * vectors and scalars
// * vectors and vectors

namespace Fluxions {

	template <typename T>
	constexpr float dot2(TVector2<T> a) {
		return dot(a, a);
	}


	template <typename T>
	constexpr float dot2(TVector3<T> a) {
		return dot(a, a);
	}

	template <typename T>
	constexpr TVector3<T> abs(TVector3<T> a) {
		return { std::abs(a.x), std::abs(a.y), std::abs(a.z) };
	}


	template <typename T>
	constexpr TVector3<T> min(TVector3<T> a, TVector3<T> b) {
		return { std::min<T>(a.x,b.x), std::min<T>(a.y, b.y), std::min<T>(a.z, b.z) };
	}


	template <typename T>
	constexpr TVector3<T> max(TVector3<T> a, TVector3<T> b) {
		return { std::max<T>(a.x,b.x), std::max<T>(a.y, b.y), std::max<T>(a.z, b.z) };
	}


	template <typename T>
	constexpr TVector3<T> max(TVector3<T> a, T b) {
		return { std::max<T>(a.x, b), std::max<T>(a.y, b), std::max<T>(a.z, b) };
	}


	template <typename T>
	constexpr float length(TVector3<T> a) {
		return std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	}
}

#endif
