#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Not sufficient or too much CML-arguments! \n");
        return 1;
    }

    string key = argv[1];

    if(strlen(key) != 26)
    {
        printf("Key needs 26char! \n");
        return 1;
    }
    bool letters[26];
    int change[26];
    for(int i = 0; i < 26; i++)
    {
        if(!(key[i] <= 'z' && key[i] >= 'a') && !(key[i] <= 'Z' && key[i] >= 'A'))
        {
           printf("Unallowed key-letters! \n");
            return 1;
        }
        letters[i] = false;
        change[i] = 0;
    }
    for(int i = 0; i < 26; i++)
    {
        if(key[i] <= 'z' && key[i] >= 'a')
        {
            letters[key[i] - 'a'] = true;
        }
        if(key[i] <= 'Z' && key[i] >= 'A')
        {
            letters[key[i] - 'A'] = true;
            key[i] = key[i] + 32;
        }
        change[i] = key[i] - 'a';
    }
    for(int i = 0; i < 26; i++)
    {
        if(letters[i] == false)
        {
            printf("Wrong Key-Syntax! %i\n", i);
            return 1;
        }
    }

    //Umwandeln
    string plain = get_string("plaintext: ");
    for(int i = 0, n = strlen(plain); i < n; i++)
    {
        if(plain[i] <= 'z' && plain[i] >= 'a')
        {
            plain[i] = 'a' + change[plain[i] - 'a'];
        }
        if(plain[i] <= 'Z' && plain[i] >= 'A')
        {
            plain[i] = 'A' + change[plain[i] - 'A'];
        }
    }

    //Ausgabe
    printf("ciphertext: %s\n", plain);
    return 0;
}