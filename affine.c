#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
  FILE *plain, *cipher, *afkey;

  int a, b, gcd;
  int m = 26;

  afkey = fopen("key.txt", "r");
  fscanf(afkey, "%d%d\n", &a, &b);

  for (int i = 1; i <= a & i <= m; i++)
  {
    if (a % i == 0 && m % i == 0)
      gcd = i;
  }

  if (gcd != 1)
  {
    printf("\n");
    printf("Key is invalid. Try another key\n");
    printf("\n");
    return 0;
  }

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
    char plaintext[1000];
    plain = fopen("plain.txt", "r");
    fscanf(plain, "%s", plaintext);

    cipher = fopen("cipher.txt", "w");

    printf("Your plaintext is '%s' \n", plaintext);

    for (int i = 0; plaintext[i] != '\0'; i++)
    {
      plaintext[i] = (a * (plaintext[i] - 'a') + b) % 26 + 'a';
      plaintext[i] = plaintext[i] - 32;
    }
    printf("Encrypted text is: '%s'\n", plaintext);
    fprintf(cipher, "%s", plaintext);
    printf("\n");
    break;
  }
  case 2:
  {
    printf("Decryption\n");
    printf("----------\n");
    int var, inv;

    for (int i = 0; i < 26; i++)
    {
      var = (a * i) % 26;
      if (var == 1)
        inv = i;
    }

    char ciphertext[1000];
    plain = fopen("cipher.txt", "r");
    fscanf(plain, "%s", ciphertext);

     printf("Your ciphertext is: '%s'\n", ciphertext);


    for (int i = 0; ciphertext[i] != '\0'; i++)
    {
      ciphertext[i] = ciphertext[i] + 32;

      ciphertext[i] = ((26 + ciphertext[i] - b - 'a') * inv) % 26 + 'a';
    }

    printf("Decrypted text is: '%s'\n", ciphertext);
    cipher = fopen("message.txt", "w");
    fprintf(cipher, "%s", ciphertext);
    printf("\n");
    break;
  }
  }

  return 0;
}