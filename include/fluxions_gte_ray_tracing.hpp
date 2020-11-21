#ifndef FLUXIONS_GTE_RAY_TRACING_HPP
#define FLUXIONS_GTE_RAY_TRACING_HPP

#include <fluxions_gte_vector_math.hpp>
#include <fluxions_gte_ray.hpp>
#include <fluxions_gte_bounding_box.hpp>

namespace Fluxions {
	static constexpr float RAY_TMAX = 1e10f;

	//// calculates whether there is an intersection with an Axis-Aligned Bounding Box
	//template <typename T>
	//constexpr bool rayIntersectsAABB(TRay<T> r, TBoundingBox<T> bbox, T tMin, T tMax) noexcept {
	//	for (unsigned i = 0; i < 3; i++) {
	//		auto invD = 1.0f / r.direction[i];
	//		auto t0 = (bbox.minBounds[i] - r.origin[i]) * invD;
	//		auto t1 = (bbox.maxBounds[i] - r.origin[i]) * invD;
	//		if (invD < 0.0f)
	//			std::swap(t0, t1);
	//		tMin = t0 > tMin ? t0 : tMin;
	//		tMax = t1 < tMax ? t1 : tMax;
	//		if (tMax <= tMin)
	//			return false;
	//	}
	//	return true;
	//}

	// calculates whether there is an intersection with an Axis-Aligned Bounding Box
	template <typename T>
	constexpr T rayIntersectsAabb(TRay<T> r, TBoundingBox<T> bbox, T tMin, T tMax) noexcept {
		for (unsigned i = 0; i < 3; i++) {
			auto invD = 1.0f / r.direction[i];
			auto t0 = (bbox.minBounds[i] - r.origin[i]) * invD;
			auto t1 = (bbox.maxBounds[i] - r.origin[i]) * invD;
			if (invD < 0.0f)
				std::swap(t0, t1);
			tMin = t0 > tMin ? t0 : tMin;
			tMax = t1 < tMax ? t1 : tMax;
			if (tMax <= tMin)
				return RAY_TMAX;
		}
		return (tMin < 0.00001f) ? tMax : tMin;
	}


	template <typename T>
	constexpr TVector3<T> aabbNormal(TVector3<T> p, TVector3<T> c) {
		const Vector3f dir = p - c;
		const Vector3f absdir = abs(dir);

		// classify main axis
		const int maindir =
			(absdir.x > absdir.y && absdir.x > absdir.z) ? 0 :
			(absdir.y > absdir.x && absdir.y > absdir.z) ? 1 :
			2;

		constexpr Vector3f NEGX{ -1.0f,  0.0f,  0.0f };
		constexpr Vector3f NEGY{ 0.0f, -1.0f,  0.0f };
		constexpr Vector3f NEGZ{ 0.0f,  0.0f, -1.0f };
		constexpr Vector3f POSX{ 1.0f,  0.0f,  0.0f };
		constexpr Vector3f POSY{ 0.0f,  1.0f,  0.0f };
		constexpr Vector3f POSZ{ 0.0f,  0.0f,  1.0f };

		// return normal based on sign of largest component
		switch (maindir) {
		case 0: return (dir.x < 0.0f) ? NEGX : POSX; break;
		case 1: return (dir.y < 0.0f) ? NEGY : POSY; break;
		case 2: return (dir.z < 0.0f) ? NEGZ : POSZ; break;
		}
		return { 0.0f,0.0f,0.0f };
	}
}

#endif
