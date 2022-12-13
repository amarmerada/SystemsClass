#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "read_ppm.h"
#include "write_ppm.h"
#include <string.h>

int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;

  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> -b <ymin> -t <ymax>\n", argv[0]); break;
    }
  }
    printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);
  
  // todo: your work here
  struct ppm_pixel** image = (struct ppm_pixel**)malloc(size*size*sizeof(struct ppm_pixel));
  memset(image, 0, (size*size*sizeof(struct ppm_pixel)));
  for(int i = 0; i < size; i++){
    image[i] = (struct ppm_pixel*)malloc(size*sizeof(struct ppm_pixel));
  }

  // generate pallet
  srand(time(0));
  struct ppm_pixel* pallette = (struct ppm_pixel*)malloc(maxIterations*sizeof(struct ppm_pixel));
  memset(pallette, 0, maxIterations*sizeof(struct ppm_pixel));
  for (int i = 0; i < maxIterations; i++){
    pallette[i].red = 100 + (rand() % 155);
    pallette[i].green = rand() % 150; 
    pallette[i].blue = 100 + (rand() % 155);
  }

  // compute image
  long double xfrac = 0;
  long double yfrac = 0;
  long double x0 = 0;
  long double y0 = 0;
  int iter = 0;
  long double x = 0, y = 0;
  long double xtmp = 0;
  double timer = 0;
  struct timeval tstart, tend;
  gettimeofday(&tstart, NULL);
  int g = 0;
  for (int i = 0; i < size; i++){ // row
    for (int j = 0; j <size; j++){ //column
      xfrac = (float)i / size;
      yfrac = (float)j / size;
      x0 = xmin + (xfrac * (xmax - xmin));
      y0 = ymin + (yfrac * (ymax - ymin));

      x = 0;
      y = 0;
      iter = 0;

      while((iter < maxIterations)&&(x*x + y*y < 4)){
        xtmp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtmp;
        iter++;
      }

      if (iter < maxIterations){
        image[i][j] = pallette[iter];
      }
      else{
        image[i][j].red = 0;
        image[i][j].green = 0;
        image[i][j].blue = 0;
      }

    }
  }
  gettimeofday(&tend, NULL);
  timer = tend.tv_sec - tstart.tv_sec + ((tend.tv_usec - tstart.tv_usec)/1.e6);
  printf("Computed mandelbrot set (%d,%d) in %g \n", size, size, timer); // all errors from this line
  const char* outputfile = "tester.ppm\0";
  write_ppm_2d(outputfile, image, size, size);
  printf("Writing to file: %s\n", outputfile);
  for(int i = 0; i < size; i++){
    free(image[i]);
  }
  free(image);
  free(pallette);
}