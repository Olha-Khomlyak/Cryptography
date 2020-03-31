#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
  int choice;

  printf("Enter operation with message\n");
  printf("encrypt - 1\n");
  printf("decrypt - 2\n");
  scanf("%d", &choice);

  FILE *plt, *sk, *ct;

  sk = fopen("key.txt", "r");
  int key;
  fscanf(sk,"%d", &key);

  switch (choice)
  {
  case 1:
  {
    char plaintext[1000];
    //int key;

    plt = fopen("plain.txt", "r");
    fscanf(plt,"%s", plaintext);

    //sk = fopen("key.txt", "r");
    //fscanf(sk,"%d", &key);

    ct = fopen("cipher.txt", "w");

    //printf("key is %d\n", key);

   // char plaintext[] = "funduk"; /* character array */
   // printf("%s\n", plaintext);

  //  int len = strlen(plaintext);
  //  printf("len= %d\n", len);

    //int key = 3;

    for (int i = 0; plaintext[i] != '\0'; i++)
    {
      plaintext[i] = plaintext[i] + key;
      if (plaintext[i] > 'z')
        plaintext[i] = plaintext[i] - 26;
      plaintext[i] = plaintext[i] - 32;
    }

    printf("Encrypted text is: %s\n", plaintext);
    fprintf(ct,"%s", plaintext);
    break;
  }
  case 2:
  {
    
    char ciphertext[1000];

    //int key;

    plt = fopen("cipher.txt", "r");
    fscanf(plt,"%s", ciphertext);

   // sk = fopen("key.txt", "r");
    //fscanf(sk,"%d", &key);

    ct = fopen("message.txt", "w");

    //printf("key is %d\n", key);
    

    printf("%s\n", ciphertext);

    for (int i = 0; ciphertext[i] != '\0'; i++)
    {
      ciphertext[i] = ciphertext[i] + 32;
      ciphertext[i] = ciphertext[i] - key;
      if (ciphertext[i] > 'z')
        ciphertext[i] = ciphertext[i] - 26;
    }
    printf("Encrypted text is: %s\n", ciphertext);
     fprintf(ct,"%s", ciphertext);
    break;
  }
  }
  return 0;
}