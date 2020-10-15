#include <stdio.h>
#include <cs50.h>

int main()
{
    int posNum;
    do{
        posNum = get_int("Positive number: ");
    } while(posNum < 1 || posNum > 8);

    //Outer Loop
    for(int i = 0; i < posNum; i++){
        //Inner Loops
        int empty = posNum - 1 - i;
        int fill = 1 + i;
        for(int k = 0; k < empty; k++){
            printf(" ");
        }
        for(int k = 0; k < fill; k++){
            printf("#");
        }
        //Middle
        printf("  ");

        for(int k = 0; k < fill; k++){
            printf("#");
        }
        /*for(int k = 0; k < empty; k++){
            printf(" ");
        }*/
        //Next line
        printf("\n");
    }
}

