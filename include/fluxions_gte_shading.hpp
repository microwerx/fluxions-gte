#ifndef FLUXIONS_GTE_SHADING_HPP
#define FLUXIONS_GTE_SHADING_HPP

#include <fluxions_gte_scalar_math.hpp>
#include <fluxions_gte_vector_math.hpp>

namespace Fluxions {
	static inline float fresnel0(float n1, float n2) {
		float R = (n1 - n2) / (n1 + n2);
		return R * R;
	}


	static inline float schlick(float cosine, float F_0) {
		return F_0 + (1.0f - F_0) * powf((1.0f - cosine), 5);
	}


	static inline Vector3f reflect(const Vector3f& v, const Vector3f& n) {
		return v - 2.0f * dot(v, n) * n;
	}


	static inline bool refract(const Vector3f& v, const Vector3f& n, float ni_over_nt, Vector3f& refracted) {
		Vector3f uv = v.unit();
		float dt = dot(uv, n);
		float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);
		if (discriminant > 0.0f) {
			refracted = ni_over_nt * (v - n * dt) - n * sqrt(discriminant);
			return true;
		}
		return false;
	}
}

#endif
