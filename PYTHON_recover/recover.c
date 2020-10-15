#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    if(argc != 2){
        printf("Usage: ./recover image\n");
        return 1;
    }

    int count = 0;
    FILE *file = fopen(argv[1], "r");
    if(file == NULL){
        printf("Usage: ./recover image\n");
        return 1;
    }
    BYTE block[512];
    int i = 512;

    fread(block, sizeof(BYTE), 512, file);
    while(!(block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && ((block[3] & 0xf0) == 0xe0))){
        if(fread(block, sizeof(BYTE), 512, file) == 0){
            printf("No JPEGs included.\n");
            return 0;
        }
    }

    char *filename = malloc(3);
    sprintf(filename, "%03i.jpg", count);
    count++;
    FILE *img = fopen(filename, "w");

    do{
    fwrite(file, sizeof(BYTE), 512, img);
    fread(block, sizeof(BYTE), 512, file);
    }while(!(block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && ((block[3] & 0xf0) == 0xe0)));

   while(1){
        if(fread(block, 1, 512, file)==0)
            break;
        if(block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && ((block[3] & 0xf0) == 0xe0)){
            free(filename);
            fclose(img);
            filename = malloc(3);
            sprintf(filename, "%03i.jpg", count);
            count++;
            img = fopen(filename, "w");
            fwrite(file, 1, 512, img);
        } else {
            fwrite(file, 1, 512, img);
        }
    }
    fclose(file);
    fclose(img);
    free(filename);
}
