#include <stdio.h>
#include <stdlib.h>

const int WIDTH = 600;
const int HEIGHT = 600;
const int RGB = 3;

void flip_horizontal (void);
unsigned char image[WIDTH][HEIGHT][RGB];

int main(){
    
    int x,y;
    
    FILE *fp;
    if((fp=fopen("Gradient.ppm","r")) == NULL){
        printf("File not there");
        return 1;
    }
    
    fscanf(fp,"P3\n600 600\n255\n");
    
    unsigned int color;
    for(x = 0; x < WIDTH; x++){ // didn't you already declare these^^
        for(y = 0; y < HEIGHT; y++){
            for(int rgb = 0; rgb < 3; rgb++){
                fscanf(fp,"%u", &color);
                image[x][y][rgb] = color;
            }
        }
    }
    
    flip_horizontal();
    
    fclose(fp);
    return 0;
}

void flip_horizontal (){
    unsigned char image_flipped[WIDTH][HEIGHT][RGB]; // new image
    
    FILE *flip = fopen("FlippedImage.ppm", "w");
    fprintf(flip, "P3\n%d %d\n255\n",WIDTH,HEIGHT); //header for new image
    
    int x, y1, y2;
    
    for(x = 0; x < WIDTH; x++){
        for(y1 = 0, y2 = HEIGHT; y1 < HEIGHT; y1++,y2--){
            for(int rgb = 0; rgb < 3; rgb++){
                image_flipped[x][y2][rgb] = image[x][y1][rgb];
            }
        }
    }
    
    for(x = 0; x < WIDTH; x++){
        for(int y = 0; y < HEIGHT; y++){
            for(int rgb = 0; rgb < 3; rgb++){
                fprintf(flip, "%i ", image_flipped[x][y][rgb]);
            }
        }
    }
    
    fclose(flip);
}
