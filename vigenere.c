#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{

    char key[100];
    char plaintext[100];

    FILE *k, *p, *c;
    k = fopen("key.txt", "r");
    fscanf(k, "%s", key);



    p = fopen("plain.txt", "r");
    fscanf(p, "%s", plaintext);

    int len = strlen(plaintext);
    //printf("len= %d\n", len);
    int keyLen = strlen(key);
    //printf("len= %d\n", keyLen);

    for (int i; i<keyLen; i++){
        if (!isalpha(key[i])){
            printf("\n");
            printf("Key is invalid\n");
            printf("\n");
            return 0;
        }
    }

    char newKey[len];
    int i, j;

    //generating new key
    for (i = 0, j = 0; i < len; ++i, ++j)
    {
        if (j == keyLen)
            j = 0;

        newKey[i] = key[j];
    }

    newKey[i] = '\0';

    //printf("New key is '%s'\n", newKey);

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

        printf("Your plaintext is '%s'\n", plaintext);

        for (int i = 0; plaintext[i] != '\0'; i++)
        {
            plaintext[i] = (plaintext[i] + newKey[i]) % 26 + 'a';
            plaintext[i] = plaintext[i] - 32;
        }
        printf("Encrypted text is: '%s'\n", plaintext);

        c = fopen("cipher.txt", "w");
        fprintf(c, "%s", plaintext);
        printf("\n");
        break;
    }
    case 2:
    {
        printf("Decryption\n");
        printf("----------\n");
        char ciphertext[1000];

        p = fopen("cipher.txt", "r");
        fscanf(p, "%s", ciphertext);
        printf("Your ciphertext is '%s'\n", ciphertext);

        for (int i = 0; ciphertext[i] != '\0'; i++)
        {
            ciphertext[i] = ciphertext[i] + 32;
            ciphertext[i] = ((ciphertext[i] - newKey[i]) + 40) % 26 + 'a';
        }

        printf("Decrypted text is: '%s'\n", ciphertext);
        c = fopen("message.txt", "w");
        fprintf(c, "%s", ciphertext);
        printf("\n");
        break;
    }
    }

    return 0;
}