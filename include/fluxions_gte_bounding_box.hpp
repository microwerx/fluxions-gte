#ifndef FLUXIONS_GTE_BOUNDING_BOX_HPP
#define FLUXIONS_GTE_BOUNDING_BOX_HPP

#include <fluxions_gte_base.hpp>
#include <fluxions_gte_vector2.hpp>
#include <fluxions_gte_vector3.hpp>
#include <fluxions_gte_vector4.hpp>

namespace Fluxions {
	template <typename T>
	class TBoundingBox {
	public:
		TBoundingBox();
		TBoundingBox(const TBoundingBox<T>& bbox);
		~TBoundingBox();
		TBoundingBox<T>& operator=(const TBoundingBox<T>& bbox);

		// resets the bounds to:
		// maxBounds(0, 0, 0)
		// minBounds(0, 0, 0)
		void reset();

		// adds the point (X, y, 0) to the box, expanding it if necessary
		void operator+=(const TVector2<T>& point);
		// adds the point (X, y, z) to the box, expanding it if necessary
		void operator+=(const TVector3<T>& point);
		// adds the point (X, y, z) to the box, expanding it if necessary
		void operator+=(const TVector4<T>& point);

		// returns true if (X, y, 0) is inside the box
		bool isPointInside(const TVector2<T>& point) const;
		// returns true if (X, y, z) is inside the box
		bool isPointInside(const TVector3<T>& point) const;
		// returns true if (X, y, z) is inside the box
		bool isPointInside(const TVector4<T>& point) const;
		const TVector3<T> size() const { return TVector3<T>(X(), Y(), Z()); }
		const TVector3<T> sizeRounded() const { return TVector3<T>((T)trunc(X() + 0.5f), (T)trunc(Y() + 0.5f), (T)trunc(Z() + 0.5f)); }
		T minXRounded() const { return (T)trunc(minX() - 0.5f); }
		T minYRounded() const { return (T)trunc(minY() - 0.5f); }
		T minZRounded() const { return (T)trunc(minZ() - 0.5f); }
		T maxXRounded() const { return (T)trunc(maxX() + 0.5f); }
		T maxYRounded() const { return (T)trunc(maxY() + 0.5f); }
		T maxZRounded() const { return (T)trunc(maxZ() + 0.5f); }
		const TVector3<T> minRounded() const { return TVector3<T>(minXRounded(), minYRounded(), minZRounded()); }
		const TVector3<T> maxRounded() const { return TVector3<T>(maxXRounded(), maxYRounded(), maxZRounded()); }
		// returns the size of box's X dimension
		T X() const { return maxBounds.x - minBounds.x; }
		// returns the size of the box's Y dimension
		T Y() const { return maxBounds.y - minBounds.y; }
		// returns the size of the box's Z dimension
		T Z() const { return maxBounds.z - minBounds.z; }
		// returns the largest size of the box's X, Y, or Z dimensions
		T maxSize() const { return max3(X(), Y(), Z()); }
		T maxSizeRounded() const { return (T)(trunc(maxSize() + 0.5f)); }
		// returns the smallest size of the box's X, Y, or Z dimensions
		T minSize() const { return min3(X(), Y(), Z()); }
		T minSizeRounded() const { return (T)(trunc(minSize() + 0.5f)); }
		// returns the size of the sphere based on the size of the box
		T radius() const { return (T)(sqrt(0.75f) * maxSize()); }
		T diameter() const { return (T)(sqrt(3.0f) * maxSize()); }
		T radiusRounded() const { return (T)(trunc(radius() + 0.5f)); }
		T diameterRounded() const { return (T)(trunc(diameter() + 0.5f)); }
		// returns the point at the center of the box
		TVector3<T> center() const;
		// returns the smallest X coordinate of the box
		T minX() const { return minBounds.x; }
		// returns the smallest y coordinate of the box
		T minY() const { return minBounds.y; }
		// returns the smallest z coordinate of the box
		T minZ() const { return minBounds.z; }
		// returns the largest X coordinate of the box
		T maxX() const { return maxBounds.x; }
		// returns the largest y coordinate of the box
		T maxY() const { return maxBounds.y; }
		// returns the largest z coordinate of the box
		T maxZ() const { return maxBounds.z; }

		TVector3<T> minBounds;
		TVector3<T> maxBounds;

		static constexpr T DefaultMaxValue = 0;
		static constexpr T DefaultMinValue = 0;
	};

	template <typename T>
	TBoundingBox<T>::TBoundingBox()
		: minBounds(DefaultMinValue, DefaultMinValue, DefaultMinValue),
		maxBounds(DefaultMaxValue, DefaultMaxValue, DefaultMaxValue) {}

	template <typename T>
	TBoundingBox<T>::TBoundingBox(const TBoundingBox<T>& bbox) {
		minBounds = bbox.minBounds;
		maxBounds = bbox.maxBounds;
	}

	template <typename T>
	TBoundingBox<T>::~TBoundingBox() {}

	template <typename T>
	TBoundingBox<T>& TBoundingBox<T>::operator=(const TBoundingBox<T>& bbox) {
		minBounds = bbox.minBounds;
		maxBounds = bbox.maxBounds;
		return *this;
	}

	template <typename T>
	void TBoundingBox<T>::reset() {
		maxBounds = TVector3<T>(DefaultMinValue, DefaultMinValue, DefaultMinValue);
		minBounds = TVector3<T>(DefaultMaxValue, DefaultMaxValue, DefaultMaxValue);
	}

	template <typename T>
	void TBoundingBox<T>::operator+=(const TVector2<T>& point) {
		*this += {point.x, point.y, 0};
	}

	template <typename T>
	void TBoundingBox<T>::operator+=(const TVector3<T>& point) {
		if (minBounds == TVector3<T>{0, 0, 0} && maxBounds == TVector3<T>{0, 0, 0}) {
			minBounds = point;
			maxBounds = point;
		}
		else {
			minBounds.x = std::min(point.x, minBounds.x);
			minBounds.y = std::min(point.y, minBounds.y);
			minBounds.z = std::min(point.z, minBounds.z);
			maxBounds.x = std::max(point.x, maxBounds.x);
			maxBounds.y = std::max(point.y, maxBounds.y);
			maxBounds.z = std::max(point.z, maxBounds.z);
		}
	}

	template <typename T>
	void TBoundingBox<T>::operator+=(const TVector4<T>& point) {
		*this += {point.x, point.y, point.z};
	}

	template <typename T>
	bool TBoundingBox<T>::isPointInside(const TVector2<T>& point) const {
		if (point.x < minBounds.x || point.x > maxBounds.x)
			return false;
		if (point.y < minBounds.y || point.y > maxBounds.y)
			return false;
		if (0 < minBounds.z || 0 > maxBounds.z)
			return false;
		return true;
	}

	template <typename T>
	bool TBoundingBox<T>::isPointInside(const TVector3<T>& point) const {
		if (point.x < minBounds.x || point.x > maxBounds.x)
			return false;
		if (point.y < minBounds.y || point.y > maxBounds.y)
			return false;
		if (point.z < minBounds.z || point.z > maxBounds.z)
			return false;
		return true;
	}

	template <typename T>
	bool TBoundingBox<T>::isPointInside(const TVector4<T>& point) const {
		if (point.x < minBounds.x || point.x > maxBounds.x)
			return false;
		if (point.y < minBounds.y || point.y > maxBounds.y)
			return false;
		if (point.z < minBounds.z || point.z > maxBounds.z)
			return false;
		return true;
	}

	template <typename T>
	TVector3<T> TBoundingBox<T>::center() const {
		return TVector3<T>(
			(maxBounds.x - minBounds.x) / 2 + minBounds.x,
			(maxBounds.y - minBounds.y) / 2 + minBounds.y,
			(maxBounds.z - minBounds.z) / 2 + minBounds.z);
	}

	using BoundingBoxf = TBoundingBox<float>;
	using BoundingBoxd = TBoundingBox<double>;
	using BoundingBoxi = TBoundingBox<int>;

#ifndef FLUXIONS_NO_EXTERN_TEMPLATES
	extern template class TBoundingBox<float>;
	extern template class TBoundingBox<double>;
	extern template class TBoundingBox<int>;
#endif
} // namespace Fluxions

#endif
