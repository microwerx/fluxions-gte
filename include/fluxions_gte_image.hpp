#ifndef FLUXIONS_GTE_IMAGE_HPP
#define FLUXIONS_GTE_IMAGE_HPP

#include <fluxions_gte_base.hpp>
#include <fluxions_gte_scalar_math.hpp>
#include <fluxions_gte_vector_math.hpp>
#include <fluxions_gte_color_math.hpp>

#ifdef _WIN32
#define FLUXIONS_GTE_USEOPENEXR 1
#elif __unix__
#define FLUXIONS_GTE_USEOPENEXR 1
#endif

namespace Fluxions {
	template <class T>
	struct is_color_type : std::integral_constant<
		bool,
		std::is_same<TColor3<T>, T>::value || std::is_same<TColor4<T>, T>::value> {};

	template <typename ColorType>
	class TImage {
	public:
		std::vector<ColorType> pixels;
		unsigned imageWidth;
		unsigned imageHeight;
		unsigned imageDepth;

		//using ImageType = TImage<ColorType>;
		using vector_type = ColorType;
		using scalar_type = typename ColorType::value_type;
		using value_type = ColorType;

		TImage()
			: imageWidth(0), imageHeight(0), imageDepth(0) {}
		TImage(int width, int height, int depth = 1) { resize(width, height, depth); }

		TImage(const TImage<ColorType>& image) {
			pixels.resize(image.pixels.size());
			std::copy(image.pixels.cbegin(), image.pixels.cend(), pixels.begin());
			imageWidth = image.imageWidth;
			imageHeight = image.imageHeight;
			imageDepth = image.imageDepth;
		}

		operator bool() const { return !pixels.empty(); }

		constexpr size_t sizeInBytes() const {
			return sizeof(*this) + pixels.size() * sizeof(ColorType);
		}

		constexpr void setBorderColor(const ColorType& color) { borderColor = color; }
		constexpr const ColorType& getBorderColor() const { return borderColor; }
		constexpr unsigned width() const { return imageWidth; }
		constexpr unsigned height() const { return imageHeight; }
		constexpr unsigned depth() const { return imageDepth; }
		constexpr unsigned pitch() const { return (unsigned)imageWidth * sizeof(value_type); }
		constexpr unsigned addr(unsigned x, unsigned y, unsigned z = 0) {
			if (x >= imageWidth || y >= imageHeight || z >= imageDepth)
				return 0;
			return z * zstride + y * imageWidth + x;
		}

		constexpr ColorType* getPixels(unsigned index) {
			if (index >= imageDepth)
				return NULL;
			return &(pixels[index * zstride]);
		}

		using iterator = typename std::vector<ColorType>::iterator;
		using const_iterator = typename std::vector<ColorType>::const_iterator;

		iterator begin() noexcept { return pixels.begin(); }
		iterator end() noexcept { return pixels.end(); }
		const_iterator cbegin() const noexcept { return pixels.cbegin(); }
		const_iterator cend() const noexcept { return pixels.cend(); }

		void resize(unsigned width, unsigned height, unsigned depth = 1);
		void reset() { resize(0, 0, 0); }
		void clear(const ColorType& clearcolor);
		bool empty() const noexcept { return pixels.empty(); }
		bool IsCubeMap() const noexcept { return imageWidth == imageHeight && imageDepth == 6; }

		bool isLikely61CubeMap() const noexcept {
			return imageWidth == imageHeight * 6;
		}

		bool isLikelyCross() const noexcept {
			return (imageWidth * 3 == imageHeight * 4) ||
				(imageWidth * 4) == (imageHeight * 3);
		}

		TImage<ColorType>& ToSRGB();
		TImage<ColorType>& ReverseSRGB();
		TImage<ColorType>& ToneMap(float exposure);
		TImage<ColorType>& ReverseToneMap(float exposure);
		void scaleColors(float x);
		TImage<ColorType> ScaleImage(unsigned newWidth, unsigned newHeight);

		constexpr void setPixel(unsigned x, unsigned y, ColorType color) noexcept {
			if (x >= imageWidth || y >= imageHeight)
				return;
			pixels[y * imageWidth + x] = color;
		}

		constexpr ColorType getPixel(unsigned x, unsigned y) const {
			if (x >= imageWidth || y >= imageHeight)
				return borderColor;

			return pixels[y * imageWidth + x];
		}

		// Same as setPixel(X, y, color) but without image bounds checking: unsafe!
		constexpr void setPixelUnsafe(unsigned x, unsigned y, ColorType color) {
			pixels[y * imageWidth + x] = color;
		}

		// Same as getPixel(X, y) but without image bounds checking: unsafe!
		constexpr ColorType getPixelUnsafe(unsigned x, unsigned y) const {
			return pixels[y * imageWidth + x];
		}

		constexpr void setPixel(unsigned x, unsigned y, unsigned z, const ColorType& color) {
			if (x >= imageWidth || y >= imageHeight || z >= imageDepth)
				return;
			pixels[z * zstride + y * imageWidth + x] = color;
		}

		constexpr ColorType getPixel(unsigned x, unsigned y, unsigned z) const {
			if (x >= imageWidth || y >= imageHeight || z >= imageDepth)
				return borderColor;

			return pixels[z * zstride + y * imageWidth + x];
		}

		//constexpr typename ColorType::type maxrgb() const noexcept {
		//	typename ColorType::type maxColorFound = 0;
		//	for (auto& c : pixels) {
		//		// maxColorFound = std::max(c.maxrgb(), maxColorFound);
		//		maxColorFound = std::max(maxof(c), maxColorFound);
		//	}
		//	return maxColorFound;
		//}

		//constexpr typename ColorType::type minrgb() const noexcept {
		//	typename ColorType::type minColorFound = pixels.empty() ? 0 : pixels[0].minrgb();
		//	for (auto& c : pixels) {
		//		minColorFound = std::min(c.minrgb(), minColorFound);
		//	}
		//	return minColorFound;
		//}

		constexpr ColorType getPixelCubeMap(const Vector3f& v) const {
			return getPixelCubeMap(v.x, v.y, v.z);
		}

		constexpr ColorType getPixelCubeMap(float x, float y, float z) const {
			if (imageDepth != 6)
				return borderColor;

			float s = 0.0f;
			float t = 0.0f;
			unsigned iz = 0;
			MakeFaceSTFromCubeVector(x, y, z, &s, &t, &iz);
			unsigned ix = (int)(s * imageWidth);
			unsigned iy = (int)((1.0f - t) * imageHeight);
			return getPixel(ix, iy, iz);
		}

		// Same as setPixel(X, y, color) but without image bounds checking: unsafe!
		constexpr void setPixelUnsafe(unsigned x, unsigned y, unsigned z, const ColorType& color) {
			pixels[(long long)z * zstride + y * imageWidth + x] = color;
		}

		// Same as getPixel(X, y) but without image bounds checking: unsafe!
		constexpr ColorType getPixelUnsafe(unsigned x, unsigned y, unsigned z) const {
			return pixels[(long long)z * zstride + y * imageWidth + x];
		}

		constexpr const void* getImageData(unsigned z) const {
			return &pixels[(long long)z * zstride];
		}

		scalar_type maxrgb() const {
			if (pixels.empty())
				return 0;
			scalar_type value = pixels[0][0];
			for (const vector_type& pixel : pixels) {
				value = std::max(
					*std::max_element(pixel.cbegin(), pixel.cend()),
					value);
			}
			return value;
		}

		scalar_type minrgb() const {
			if (pixels.empty())
				return 0;
			scalar_type value = pixels[0][0];
			for (const vector_type& pixel : pixels) {
				value = std::min<scalar_type>(
					*std::min_element(pixel.cbegin(), pixel.cend()),
					value);
			}
			return value;
		}

		double getTotalIntensity() const;
		double getMinIntensity() const;
		double getMaxIntensity() const;
		double getMeanIntensity() const;
		int getNumPixels() const { return (int)pixels.size(); }

		// TODO: change these to
		// * savePPM
		// * saveEXR
		// * saveCubePPM
		// * saveCubeEXR
		// * saveCubePFM
		// * savePFM
		//void savePPMRaw(const std::string& filename, unsigned z = 0) const;
		bool savePPM(const std::string& filename, unsigned z = 0, bool flipy = false) const;
		bool savePPMi(const std::string& filename, float scale, int minValue, int maxValue, unsigned z = 0, bool flipy = false) const;
		bool saveCubePPM(const std::string& filename, bool flipy = false) const;
		bool saveCubePPMi(const std::string& filename, float scale, int minValue, int maxValue, bool flipy = false) const;
		//void savePPMHDRI(const std::string& filename, unsigned z = 0) const;

		// TODO: change these to
		// * loadPPM
		// * loadEXR
		// * loadCubePPM
		// * saveCubeEXR
		bool loadPPM(const std::string& path);
		bool loadPFM(const std::string& path);
		bool loadPGM(const std::string& path);
		bool savePFM(const std::string& path) const;
		bool loadEXR(const std::string& path);
		bool saveEXR(const std::string& path) const;

		bool flipX(int z = 0);
		bool flipY(int z = 0);
		bool flipXY(int z = 0);
		bool rotateLeft90(int z = 0);
		bool rotateRight90(int z = 0);

		// blit2D copies a rectangle into the same image type dst
		void blit2D(int sx, int sy, int sz,
					int width, int height,
					int dx, int dy, int dz,
					TImage<ColorType>& dst) const;

		// blit3D copies a cube into the same image type dst
		void blit3D(int sx, int sy, int sz,
					int width, int height, int depth,
					int dx, int dy, int dz,
					TImage<ColorType>& dst) const;

		static constexpr int SwizzleDefault = 0;
		static constexpr int SwizzleCorona = 1;
		static constexpr int SwizzleRotateZUp = 2;

		// option = 0, do default
		// option = 1, do Corona swizzle
		// option = 2, do Z up
		bool convertRectToCubeMapEx(TImage<ColorType>& dst, int swizzle);
		bool convertCubeMapToRectEx(TImage<ColorType>& dst, int swizzle);

		// Converts 6x1 rectangle to cube map
		bool convertRectToCubeMapEx(int swizzle);
		// Converts cube map to 6x1 rectangle
		bool convertCubeMapToRectEx(int swizzle);

		// Converts Corona style 6x1 rectangle to cube map
		bool convertRectToCubeMap();
		// Converts cube map to Corona style 6x1 rectangle
		bool convertCubeMapToRect();
		// Converts Corona style 6x1 rectangle to cube map
		bool convertRectToCubeMap(TImage<ColorType>& dst) const;
		// Converts cube map to Corona style 6x1 rectangle
		bool convertCubeMapToRect(TImage<ColorType>& dst) const;

		// Converts either horizontal cross or vertical cross to cube map
		bool convertCrossToCubeMap();
		// Converse cube map to vertical cross format
		bool convertCubeMapToCross(bool horizontal = false);
		// Converts either horizontal cross or vertical cross to cube map
		bool convertCrossToCubeMap(TImage<ColorType>& dst) const;
		// Converts cube map to vertical cross format
		bool convertCubeMapToCross(TImage<ColorType>& dst, bool horizontal = false) const;

		// Copies GL_FLOAT or GL_UNSIGNED_BYTE raw data
		void setImageData(unsigned int format, unsigned int type, unsigned width, unsigned height, unsigned depth, void* _pixels);

	private:
		void _setImageData(unsigned int fromFormat, unsigned int fromType, unsigned int toFormat, unsigned int toType, unsigned width, unsigned height, unsigned depth, void* _pixels);

		unsigned zstride;
		unsigned ystride;
		ColorType borderColor;
		int minColor;
		int maxColor;
	};

	using Image3f = TImage<Color3f>;
	using Image3i = TImage<Color3i>;
	using Image3ub = TImage<Color3ub>;
	using Image3us = TImage<Color3us>;

	using Image4f = TImage<Color4f>;
	using Image4i = TImage<Color4i>;
	using Image4us = TImage<Color4us>;
	using Image4ub = TImage<Color4ub>;

#ifndef FLUXIONS_NO_EXTERN_TEMPLATES
	extern template class TImage<Color3f>;
	extern template class TImage<Color3i>;
	extern template class TImage<Color3us>;
	extern template class TImage<Color3ub>;

	extern template class TImage<Color4f>;
	extern template class TImage<Color4i>;
	extern template class TImage<Color4us>;
	extern template class TImage<Color4ub>;
#endif
} // namespace Fluxions

#endif
