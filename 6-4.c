#include <stdio.h>
#include <stdlib.h>

const int WIDTH = 600;
const int HEIGHT = 600;
const int RGB = 3;
const int ALL = HEIGHT*WIDTH*RGB;

void flip_horizontal (void);
unsigned char image[ALL];

int main(){
    
    int x,y;
    
    FILE *fp;
    if((fp=fopen("Gradient.ppm","r")) == NULL){
        printf("File not there");
        return 1;
    }
    
    fscanf(fp,"P3\n600 600\n255\n");
    
    unsigned int color, count = 0;
    for(x = 0; x < WIDTH; x++){ // didn't you already declare these^^
        for(y = 0; y < HEIGHT; y++){
            for(int rgb = 0; rgb < 3; rgb++){
                fscanf(fp,"%u", &color);
                *(image + count) = color;
                count++;
            }
        }
    }
    
    flip_horizontal();
    
    fclose(fp);
    return 0;
}

void flip_horizontal (){
    unsigned char image_flipped[ALL]; // new image
    
    FILE *flip = fopen("FlippedImage.ppm", "w");
    fprintf(flip, "P3\n%d %d\n255\n",WIDTH,HEIGHT); //header for new image
    
    unsigned int x, w, w2 = 0,row = 1;
    
    for(x = 0, w = (WIDTH*3)-3; x < ALL; x+=3,w-=3){
        for(w2 = 0; w2 < 3; w2++){
            *(image_flipped + w + w2) = *(image + x + w2);
        }
        
        if (w % 1800 == 0){
            row++;
            w = (WIDTH*row*3);
            
        }
    }
    
    for(x = 0; x < ALL; x++){
        fprintf(flip, "%i ", *(image_flipped+x));
    }
    
    fclose(flip);
}

