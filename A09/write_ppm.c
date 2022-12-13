#include "write_ppm.h"
#include <stdio.h>
#include <string.h>

void write_ppm_2d(const char* filename, struct ppm_pixel** pixels, int w, int h) {
    
    FILE *fp;
    fp = fopen(filename, "wb");
    char header[18] = "P6\n#C \n%d %d\n255\n";
    fprintf(fp, header, w, h);

    for (int i = 0; i < (h); i++){ // should be i < h
        for (int j = 0; j < (w); j++){
            fwrite(&pixels[i][j].red, 1, 1, fp);
            fwrite(&pixels[i][j].green, 1, 1, fp);
            fwrite(&pixels[i][j].blue, 1, 1, fp);
        }
    }
    printf("writing to file...\n");


    fclose(fp);

}