#include "write_ppm.h"
#include <stdio.h>
#include <string.h>

void write_ppm_2d(const char* filename, struct ppm_pixel** pixels, int w, int h) {
    FILE *fp;
    fp = fopen(filename, "wb");
    fprintf(fp, "P6\n#Created by GIMP version 2.10.24 PNM plug-in\n%d %d\n255\n", w, h);

    for (int i = 0; i < h; i++){ // should be i < h
        for (int j = 0; j < w; j++){
            fwrite(&pixels[i][j].red, 1, 1, fp);
            fwrite(&pixels[i][j].green, 1, 1, fp);
            fwrite(&pixels[i][j].blue, 1, 1, fp);
        }
    }

    fclose(fp);

}