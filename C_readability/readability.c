#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(){
    string text = get_string("Text: ");
    int countL = 0;
    int countW = 1;
    int countS = 0;

    string adjstr = "";
    // Find #'s
    for(int i = 0, n = (int) strlen(text); i < n; i++)
    {
        // Find #Letters
        if((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            countL++;
        }

        // Find #Words
        if(text[i] == ' ')
        {
            countW++;
        }

        // Find #Sentences
        if(text[i] == '!' || text[i] == '?' || text[i] == '.')
        {
            countS++;
        }
    }

    float index = 0.0588 * (countL * 100 / (float) countW) - 0.296 * (countS * 100 / (float) countW) - 15.8;

    //adjustements
    if(index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if(index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %.0f\n", index);
    }
}