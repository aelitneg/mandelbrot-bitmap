#include "FractalCreator.h"

namespace mandelbrot_bitmap {
	FractalCreator::FractalCreator(int width, int height) : width_(width),
		height_(height),
		histogram_(new int[Mandelbrot::kMaxIterations]{ 0 }),
		fractal_(new int[width_ * height_]{ 0 }),
		bitmap_(width_, height_),
		zoomList_(width_, height_) {

		zoomList_.Add(Zoom(width_ / 2, height_ / 2, 4.0 / width_));
	}

	void FractalCreator::AddRange(double rangeEnd, const RGB& rgb) {
		ranges_.push_back(rangeEnd * Mandelbrot::kMaxIterations);
		colors_.push_back(rgb);

		if (got_first_range_) {
			range_totals_.push_back(0);
		}

		got_first_range_ = true;
	}

	void FractalCreator::AddZoom(const Zoom& zoom) {
		zoomList_.Add(zoom);
	}

	void FractalCreator::Run(string filename) {
		CalculateIterations();
		CalculateTotalIterations();
		CalculateRangeTotals();

		DrawFractal();

		WriteBitmap(filename);
	}

	void FractalCreator::CalculateIterations() {
		for (int y = 0; y < height_; y++) {
			for (int x = 0; x < width_; x++) {
				pair <double, double> coordinates = zoomList_.DoZoom(x, y);

				int iterations = Mandelbrot::GetIterations(coordinates.first, coordinates.second);

				fractal_[y * width_ + x] = iterations;

				if (iterations != Mandelbrot::kMaxIterations) {
					histogram_[iterations]++;
				}
			}
		}
	}

	void FractalCreator::CalculateTotalIterations() {
		for (int i = 0; i < Mandelbrot::kMaxIterations; i++) {
			total_ += histogram_[i];
		}
	}

	void FractalCreator::CalculateRangeTotals() {
		int range_index = 0;

		for (int i = 0; i < Mandelbrot::kMaxIterations; i++) {
			int pixels = histogram_[i];

			if (i >= ranges_[range_index + 1]) {
				range_index++;
			}

			range_totals_[range_index] += pixels;
		}
	}

	int FractalCreator::GetRange(int iterations) const{
		int range = 0;

		for (int i = 1; i < ranges_.size(); i++) {
			range = i;

			if (ranges_[i] > iterations) {
				break;
			}
		}

		range--;

		assert(range > -1);
		assert(range < ranges_.size());

		return range;
	}

	void FractalCreator::DrawFractal() {
		for (int y = 0; y < height_; y++) {
			for (int x = 0; x < width_; x++) {
				uint8_t red = 0;
				uint8_t green = 0;
				uint8_t blue = 0;

				int iterations = fractal_[y * width_ + x];

				int range = GetRange(iterations);
				int rangeTotal = range_totals_[range];
				int rangeStart = ranges_[range];

				RGB& startColor = colors_[range];
				RGB& endColor = colors_[range + 1];

				RGB colorDiff = endColor - startColor;

				if (iterations != Mandelbrot::kMaxIterations) {
					int totalPixels = 0;

					for (int i = rangeStart; i <= iterations; i++) {
						totalPixels += histogram_[i];
					}

					red = startColor.r + colorDiff.r * (double)totalPixels / rangeTotal;
					green = startColor.g + colorDiff.g * (double)totalPixels / rangeTotal;
					blue = startColor.b + colorDiff.b * (double)totalPixels / rangeTotal;
				}

				bitmap_.SetPixel(x, y, red, green, blue);
			}
		}
	}

	void FractalCreator::WriteBitmap(string filename) {
		bitmap_.Write(filename);
	}
}
