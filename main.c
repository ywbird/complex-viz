#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>

#include "hsl2rgb.h"

typedef uint8_t u8;

typedef float f32;
typedef double f64;
typedef double complex c64;

f64 sig(f64 x);
c64 csig(c64 x);

#define WIDTH 1000
#define HEIGHT 1000

#define BOX_START_X (-3.0)
#define BOX_END_X (3.0)
#define BOX_START_Y (-3.0)
#define BOX_END_Y (3.0)

int main()
{
  const char *output_path = "output.ppm";
  FILE *f = fopen(output_path, "wb");

  fprintf(f, "P6\n");
  fprintf(f, "%d %d\n", WIDTH, HEIGHT);
  fprintf(f, "255\n");

  for (size_t y = 0; y < HEIGHT; y++) {
    for (size_t x = 0; x < WIDTH; x++) {
      f64 u = (f64)x / (f64)WIDTH * (BOX_END_X - BOX_START_X) + BOX_START_X;
      f64 v = (f64)y / (f64)HEIGHT * (BOX_END_Y - BOX_START_Y) + BOX_START_Y;

      c64 z = catanh(u+v*I);

      // f64 hue = sig(creal(z));
      // f64 lightness = sig(cimag(z));

      f64 hue = fmod(fmod((f32)creal(z), 1.0)+1.0, 1.0);
      f64 lightness = fmod(fmod((f32)cimag(z), 1.0)+1.0, 1.0);

      RGB rgb = hsl2rgb(hue, 1.0, lightness);

      fputc((u8)(rgb.r), f);
      fputc((u8)(rgb.g), f);
      fputc((u8)(rgb.b), f);
    }
  }

  printf("Generated %s\n", output_path);

  return 0;
}

f64 sig(f64 x)
{
  return 1 / ( 1 + exp(-x) );
  // return (x / ( 1.0 + fabs(x) ) + 1.0) / 2.0;
}

c64 csig(c64 x)
{
  return 1 / ( 1 + cexp(-x) );
  // return (x / ( 1.0 + fabs(x) ) + 1.0) / 2.0;
}
