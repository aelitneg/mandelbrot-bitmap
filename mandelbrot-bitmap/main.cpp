#include "FractalCreator.h"

using namespace std;
using namespace mandelbrot_bitmap;

int main() {
	int kHeight = 600;
	FractalCreator fractalCreator(800, 600);
	
	fractalCreator.AddZoom(Zoom(295, kHeight - 202, 0.1));
	fractalCreator.AddZoom(Zoom(312, kHeight - 304, 0.1));

	fractalCreator.CalculateIterations();
	fractalCreator.CalculateTotalIterations();

	fractalCreator.DrawFractal();

	fractalCreator.WriteBitmap("mandelbrot.bmp");

	return 0;
}