#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include "read_ppm.h"
#include "write_ppm.h"
#include "string.h"

int maxIterations = 1000;

void compute_image(struct ppm_pixel** image, struct ppm_pixel* palette, int startCol, int endCol, int startRow, int endRow, int size, float xmin, float xmax, float ymin, float ymax){
  long double xfrac = 0;
  long double yfrac = 0;
  long double x0 = 0;
  long double y0 = 0;
  int iter = 0;
  long double x = 0, y = 0;
  long double xtmp = 0;
  double timer = 0;
  struct timeval tstart, tend;
  int g = 0;
  
  for (int i = startRow; i < endRow; i++){ // row
    for (int j = startCol; j < endCol; j++){ //column
      
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
        printf("after here--------- i: %d  j: %d\n", i, j);
        image[i][j] = palette[iter]; // something is wrong with this code
        printf("made it thru---------\n");  
      }
      else{
        image[i][j].red = 0;
        image[i][j].green = 0;
        image[i][j].blue = 0;
      }
      printf("column forloop\n");
    }
    printf("row forloop\n");
  }

  return;
}

int main(int argc, char* argv[]){
  double timer = 0;
  struct timeval tstart, tend;
   gettimeofday(&tstart, NULL);
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  

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

//generate pallette
int shmid0;
shmid0 = shmget(IPC_PRIVATE, sizeof(struct ppm_pixel)* maxIterations, 0660 | IPC_CREAT);// 0644
if (shmid0 == -1){
  perror("Cannot initialize shared memory for palette\n");
  exit(1);
}

srand(time(0));

struct ppm_pixel* pallette = shmat(shmid0, NULL, 0);
if(pallette == (void*)-1){
  perror("Cannot access shared memory for pallette");
}

  memset(pallette, 0, maxIterations*sizeof(struct ppm_pixel));
  for (int i = 0; i < maxIterations; i++){
    pallette[i].red = 100 + (rand() % 155);
    pallette[i].green = rand() % 150; 
    pallette[i].blue = 100 + (rand() % 155);
  }

//allocate array of pixels using shared memory
int shmid;
shmid = shmget(IPC_PRIVATE, sizeof(struct ppm_pixel**)*size*size, IPC_CREAT | 0660);
if(shmid == -1){
  perror("can't initialize shm\n");
  exit(1);
}

struct ppm_pixel** image = shmat(shmid, NULL, 0);
if(image == (void*)-1){
  perror("can't access shm");
  exit(1);
}

for(int i = 0; i < 4; i++){
  fflush(stdout);
  int pid = fork();
  if(pid == 0){
    if(i == 0 ){
      printf("%d) block: (0,0) to (240, 240)\n", getpid());
      fflush(stdout);
      compute_image(image, palette, 0, 240, 0, 240, );
    }
  }
}


for(int i = 0; i < 4; i++){
  int status;
  int pid = wait(&status);
  printf("Child process complete %d\n", pid);
}

//save final image using write ppm

const char* outputfile = "tester2.ppm\0";
write_ppm_2d(outputfile, image, size, size);

if(shmdt(image) == -1){
  perror("can't detach from shm\n");
  exit(1);
}

if (shmctl(shmid, IPC_RMID, 0) == -1) {
    perror("can't remove shm\n");
    exit(1);
  }

//output number of seconds needed to compute image

gettimeofday(&tend, NULL);
  timer = tend.tv_sec - tstart.tv_sec + ((tend.tv_usec - tstart.tv_usec)/1.e6);
  printf("Computed mandelbrot set (%d,%d) in %g \n", size, size, timer); // all errors from this line
 
//print pids and work tasks (id, sub-image block cols (0, 240) rows (0, 240))


  return 0;
}