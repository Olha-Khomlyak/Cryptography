#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(void)
{
	int i, j, x, det;
	int keyMatrix[2][2];

	FILE* arr, * pl, * ci;
	arr = fopen("key.txt", "r");

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 2; j++)
		{
			fscanf(arr, "%d\t", &keyMatrix[i][j]);
		}
	}
	det = keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0];
	if (det == 0) {
		printf("\n");
		printf("Key is invalid\n");
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
		char plain[100];

		pl = fopen("plain.txt", "r");
		fscanf(pl, "%s", plain);

		for (int i = 0; plain[i] != '\0'; i++)
		{
			plain[i] = plain[i] - 32;
		}
		printf("Your plaintext is '%s'\n", plain);

		char CipherText[100] = "";
		int messageVector[2][1];
		printf("\n");
		int cipherMatrix[3][1];
		

		for (int i = 0; plain[i] != '\0';)
		{
			messageVector[i % 2][0] = (plain[i]) % 65;
			messageVector[(i + 1) % 2][0] = (plain[i + 1]) % 65;
			
			for (int k = 0; k < 2; k++)
			{
				for (j = 0; j < 1; j++)
				{
					cipherMatrix[k][j] = 0;

					for (x = 0; x < 2; x++)
					{
						cipherMatrix[k][j] += keyMatrix[k][x] * messageVector[x][j];
					}

					cipherMatrix[k][j] = cipherMatrix[k][j] % 26;
					CipherText[i] = cipherMatrix[k][j] + 65;
					i++;
				}
			}
		
		}

		printf("Your ciphertext is '%s'\n", CipherText);
		ci = fopen("cipher.txt", "w");
		fprintf(ci, "%s", CipherText);
		printf("\n");

		break;
	}
	case 2:
	{
		char cipher[100];
		pl = fopen("cipher.txt", "r");
		fscanf(pl, "%s", cipher);

		//inverse of KeyMatrix
		det = keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0];
		int anew[2][2];
		int inverse[2][2];

		anew[0][0] = keyMatrix[1][1];
		anew[0][1] = -keyMatrix[0][1] + 26;
		anew[1][0] = -keyMatrix[1][0] + 26;
		anew[1][1] = keyMatrix[0][0];

		int var, inv;

		for (int i = 0; i < 26; i++)
		{
			var = (det * i) % 26;
			if (var == 1)
				inv = i;
		}


		for (i = 0; i < 2; i++)
		{
			for (j = 0; j < 2; j++)
			{
				inverse[i][j] = inv * anew[i][j] % 26;
			}
		}
        
        char MessageText[100] = "";
        int cipherMatrix[2][1];
		int Message[3][1];

		for (int i = 0; cipher[i] != '\0';)
		{
			cipherMatrix[i % 2][0] = (cipher[i]) % 65;
			cipherMatrix[(i + 1) % 2][0] = (cipher[i + 1]) % 65;
			
			for (int s = 0; s < 2; s++)
			{
				for (j = 0; j < 1; j++)
				{
					Message[s][j] = 0;

					for (x = 0; x < 2; x++)
					{
						Message[s][j] += inverse[s][x] * cipherMatrix[x][j];
					}

					Message[s][j] = Message[s][j] % 26;
					MessageText[i] = Message[s][j] + 65 + 32 ;
					i++;
				}
			}
		
		}
		printf("Your message is '%s'\n", MessageText);
		ci = fopen("message.txt", "w");
		fprintf(ci, "%s", MessageText);
		printf("\n");
		break;
	}
	}
}