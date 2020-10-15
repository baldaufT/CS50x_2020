#include <stdio.h>
#include <cs50.h>

int main(){
    long num = 0;
    int checkSum = 1;

    do{
        num = get_long("What's your credit number? ");
    } while(num < 1);
    if(num >= 10000000000000000 || num < 1000000000000 || (num < 100000000000000 && num >= 10000000000000)){
        printf("INVALID\n");
    } else{
        // Calculate checkSum
        long counter = 10;
        long zwischen = 0;
        do{
           zwischen = num % counter;
           checkSum += zwischen / (counter / 10);
           counter *= 100;
           zwischen = 0;
        } while(num / (counter / 100) != 0);
        zwischen = 0;
        counter = 100;
        do{
           zwischen = num % counter;
           zwischen = (zwischen / (counter / 10)) * 2;
           if(zwischen < 10){
               checkSum += zwischen;
           } else {
               checkSum += zwischen / 10;
               checkSum += zwischen % 10;
           }
           counter *= 100;
           zwischen = 0;
        } while(num / (counter / 100) != 0);

        //checkSum abchecken
        if((checkSum - 1) % 10 != 0){
            printf("INVALID\n");
        }
        else{
            //get length and check if starts with right number
            //AMEX
            if(num / 10000000000000 == 34 || num / 10000000000000 == 37){
                printf("AMEX\n");
            } else
            //Mastercard
            if(num / 100000000000000 > 50 && num / 100000000000000 < 56){
                printf("MASTERCARD\n");
            } else
            //VISA
            if(num / 1000000000000000 == 4 || num / 1000000000000 == 4){
                printf("VISA\n");
            } else {
                printf("INVALID\n");
            }
        }
    }
}
