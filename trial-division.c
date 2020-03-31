#include <stdio.h>
#include <gmp.h>
#include <time.h>
#include <time.h>

int main()
{
	mpz_t n;
	mpz_init(n);

	printf("Enter n: ");
	gmp_scanf("%Zd", n);

	mpz_t z;
	mpz_init(z);

	mpz_t i;
	mpz_init(i);
	mpz_set_ui(i, 3); // checking if n can be divided by each number from 3 to sqrt(n)

	int flag = 0;

	mpz_t sr;
	mpz_init(sr);

	mpz_sqrt(sr, n);//sr = square root of n

	clock_t t;
	t = clock();

	while (mpz_cmp(sr, i) > 0) // until i<sr 
	{
		mpz_mod(z, n, i); //z=n(mod i)
		if (mpz_cmp_ui(z, 0) == 0) //if z==0
		{
			gmp_printf("The nontrivial factor of %Zd is %Zd\n",n,i);
			flag = 1;
		}
		if (flag == 1)
		{
			t = clock() - t;
			double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
			printf("Timing: %f seconds \n", time_taken);
			return 0;
		}
		
		mpz_add_ui(i, i, 1); // i=i+1
	}
	return 0;
}
