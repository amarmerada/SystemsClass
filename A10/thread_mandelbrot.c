#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"
#include <string.h>
struct args{
  int startcol;
  int endcol;
  int startrow;
  int endrow;
  int size;
  int xmax;
  int ymax;
  int xmin;
  int ymin;
  int maxIterations;
  struct ppm_pixel* pallette;
  struct ppm_pixel** image; // how do i make this shared???????
};


int thread_mand( void *arguments){
  struct args thread_args = (struct args)arguments;

 long double xfrac = 0;
  long double yfrac = 0;
  long double x0 = 0;
  long double y0 = 0;
  int iter = 0;
  long double x = 0, y = 0;
  long double xtmp = 0;
  double timer = 0;
  struct timeval tstart, tend;
  //gettimeofday(&tstart, NULL);
  int g = 0;
  for (int i = 0; i < thread_args.size; i++){ // row
    for (int j = 0; j <thread_args.size; j++){ //column
      xfrac = (float)i / thread_args.size;
      yfrac = (float)j / thread_args.size;
      x0 = thread_args.xmin + (xfrac * (thread_args.xmax - thread_args.xmin));
      y0 = thread_args.ymin + (yfrac * (thread_args.ymax - thread_args.ymin));

      x = 0;
      y = 0;
      iter = 0;

      while((iter < thread_args.maxIterations)&&(x*x + y*y < 4)){
        xtmp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtmp;
        iter++;
      }

      if (iter < thread_args.maxIterations){
        thread_args.image[i][j] = thread_args.pallette[iter];
      }
      else{
        thread_args.image[i][j].red = 0;
        thread_args.image[i][j].green = 0;
        thread_args.image[i][j].blue = 0;
      }

    }
  }
  return 0;
}


int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;
  int numProcesses = 4;

  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:p:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> "
        "-b <ymin> -t <ymax> -p <numProcesses>\n", argv[0]); break;
    }
  }
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  Num processes = %d\n", numProcesses);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);
 
  struct ppm_pixel** image = (struct ppm_pixel**)malloc(size*size*sizeof(struct ppm_pixel));
  for(int i = 0; i < size; i++){
    image[i] = (struct ppm_pixel*)malloc(size*sizeof(struct ppm_pixel));
  }


  srand(time(0));
  struct ppm_pixel* pallette = (struct ppm_pixel*)malloc(maxIterations*sizeof(struct ppm_pixel));

  for (int i = 0; i < maxIterations; i++){
    pallette[i].red = 100 + (rand() % 155);
    pallette[i].green = rand() % 150; 
    pallette[i].blue = 100 + (rand() % 155);
  }
  pthread_t thread1_id;
  struct args args1;
  args1.startcol = 0;
  args1.startrow = 0;
  args1.endcol = 240;
  args1.endrow = 240;
  args1.size = 480;
  args1.maxIterations = 1000;
  args1.pallette = pallette;
  args1.image = image;
  args1.xmax = xmax;
  args1.ymax = ymax;
  args1.xmin = xmin;
  args1.ymin = ymin;
  pthread_create(&thread1_id, NULL, thread_mand, (void*)args1);
  pthread_t thread2_id;
  struct args args2;
  args2.startcol = 0;
  args2.startrow = 240;
  args2.endcol = 240;
  args2.endrow = 480;
  args2.size = 480;
  args2.maxIterations = 1000;
  args2.pallette = pallette;
  args2.image = image;
  args2.xmax = xmax;
  args2.ymax = ymax;
  args2.xmin = xmin;
  args2.ymin = ymin;
  pthread_create(&thread2_id, NULL, thread_mand, (void*)args2);
  pthread_t thread3_id;
  struct args args3;
  args3.startcol = 240;
  args3.startrow = 240;
  args3.endcol = 480;
  args3.endrow = 480;
  args3.size = 480;
  args3.maxIterations = 1000;
  args3.pallette = pallette;
  args3.image = image;
  args3.xmax = xmax;
  args3.ymax = ymax;
  args3.xmin = xmin;
  args3.ymin = ymin;
  pthread_create(&thread3_id, NULL, thread_mand, (void*)args3);
  pthread_t thread4_id;
  struct args args4;
  args2.startcol = 240;
  args2.startrow = 0;
  args2.endcol = 480;
  args2.endrow = 240;
  args2.size = 480;
  args2.maxIterations = 1000;
  args2.pallette = pallette;
  args2.image = image;
  args2.xmax = xmax;
  args2.ymax = ymax;
  args2.xmin = xmin;
  args2.ymin = ymin;
  pthread_create(&thread4_id, NULL, thread_mand, (void*)args4);
  pthread_join(thread1_id, NULL);
  pthread_join(thread2_id, NULL);
  pthread_join(thread3_id, NULL);
  pthread_join(thread4_id, NULL);

 
  //gettimeofday(&tend, NULL);
  //timer = tend.tv_sec - tstart.tv_sec + ((tend.tv_usec - tstart.tv_usec)/1.e6);
  printf("Computed mandelbrot set (%d,%d) in -- \n", size, size); // all errors from this line //timer
  const char* outputfile = "tester.ppm\0";
  write_ppm_2d(outputfile, image, size, size);
  printf("Writing to file: %s\n", outputfile);
  for(int i = 0; i < size; i++){
    free(image[i]);
  }
  free(image);
  free(pallette);
}
