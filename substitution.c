#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void)
{
    printf("\n\n");
    srand(time(NULL));

    FILE *plain, *ciphher, *k;

    char oldkey[26] = "abcdefghijklmnopqrstuvwxyz";
    // char key[26] = "abcdefghijklmnopqrstuvwxyz"; /* character array */
    char key[26];
    k = fopen("key.txt", "r");
    fscanf(k, "%s", key);

    //------> english alphabet permutation
    // int len = strlen(key);
    // char temp;

    // for (int i = 0; i < len; i++)
    // {
    //     int j = (rand() % len);
    //     temp = key[j];
    //     key[j] = key[i];
    //     key[i] = temp;
    // }
    //

    printf("\n\n");

    char plaintext1[1000];
    char *result, *result2;
    long int position, position2;

    int choice;
    printf("\n");
    printf("Choose operation with message:\n");
    printf("For encryption type 1\n");
    printf("For decryption type 2\n");
    printf("------------------------\n");
    scanf("%d", &choice);
    printf("\n");

    switch (choice)
    {
    case 1:
    {
        printf("Encryption\n");
        printf("----------\n");
        //printf("Your key is '%s'\n", key);

        plain = fopen("plain.txt", "r");
        fscanf(plain, "%s", plaintext1);
        printf("Your plaintext is '%s'\n", plaintext1);

        ciphher = fopen("cipher.txt", "w");

        int lp = strlen(plaintext1);

        char *cipher = malloc(lp + 1);

        for (int i = 0; plaintext1[i] != '\0'; i++)
        {
            result = strchr(oldkey, plaintext1[i]);
            position = result - oldkey;
            cipher[i] = key[position];
            //printf("%c\n",key[position]);
            //printf("%ld\n",position);
        }
        printf("Your ciphertext is '%s'\n", cipher);
        fprintf(ciphher, "%s", cipher);

        // k = fopen("subkey.txt", "w");
        // fprintf(k, "%s", key);

        printf("\n");
        break;
    }
    case 2:
    {
        printf("Decryption\n");
        printf("----------\n");

        char cipher[1000];
        char dkey[1000];

        k = fopen("key.txt", "r");
        fscanf(k, "%s", dkey);
        //printf("Your key is '%s'\n", dkey);

        plain = fopen("cipher.txt", "r");
        fscanf(plain, "%s", cipher);
        printf("Your ciphertext is '%s'\n", cipher);

        int lp = strlen(cipher);

        char *message = malloc(lp + 1);

        for (int i = 0; cipher[i] != '\0'; i++)
        {
            result2 = strchr(dkey, cipher[i]);
            position2 = result2 - dkey;
            //printf("%ld\n",position2);
            message[i] = oldkey[position2];
            //printf("%c\n",oldkey[position2]);
            // printf("%ld\n",position);
        }
        printf("Your message is '%s'\n", message);
        ciphher = fopen("message.txt", "w");
        fprintf(ciphher, "%s", message);
        printf("\n");
        break;

        return 0;
    }
    }
}