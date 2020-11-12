#include "FractalCreator.h"
#include "Zoom.h"

using namespace std;
using namespace mandelbrot_bitmap;

int main() {
	FractalCreator fractalCreator(800, 600);

	fractalCreator.AddRange(0.0, RGB(0, 0, 0));
	fractalCreator.AddRange(0.3, RGB(255, 0, 0));
	fractalCreator.AddRange(0.5, RGB(25, 255, 0));
	fractalCreator.AddRange(1.0, RGB(255, 255, 255));

	fractalCreator.AddZoom(Zoom(295, 202, 0.1));
	fractalCreator.AddZoom(Zoom(312, 304, 0.1));

	fractalCreator.Run("mandelbrot.bmp");

	return 0;
}