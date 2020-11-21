#ifndef FLUXIONS_GTE_IMAGE_OPERATIONS_HPP
#define FLUXIONS_GTE_IMAGE_OPERATIONS_HPP

#include <fluxions_gte_image.hpp>

namespace Fluxions {
	template <typename ColorType>
	ColorType maxof(const TImage<ColorType>& image) noexcept {
		ColorType found = *image.cbegin();
		for (const auto& p : image) {
			found = std::max(found, maxof(p));
		}
		return found;
	}

	template <typename ColorType>
	ColorType minof(const TImage<ColorType>& image) noexcept {
		ColorType found = *image.cbegin();
		for (const auto& p : image) {
			found = std::min(found, minof(p));
		}
		return found;
	}

	// For every pixel in src, p = scale * pow(2^stops * p, gamma)
	template <typename ColorType>
	TImage<ColorType>& gammaCorrect(TImage<ColorType>& src, float scale, float stops, float gamma) {
		float exposure = stopsToExposure(stops);
		for (auto& p : src.pixels) {
			p = scaleExposeGamma(p, scale, exposure, gamma);
		}
		return src;
	}
}

#endif
