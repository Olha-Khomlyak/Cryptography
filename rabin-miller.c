#include <gmp.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool Rabin_Miller_Test(mpz_t p, int s)
{

	mpz_t n;
	mpz_init(n);
	mpz_sub_ui(n, p, 1); //n=p-1

	mpz_t r;
	mpz_init(r);

	bool res = false;
	int u = 0;

	// finding u an r, such that p-1=(2^u)*r
	while (mpz_mod_ui(r, n, 2) == 0)
	{
		u++;
		mpz_divexact_ui(r, n, 2);
		mpz_set(n, r);
	}
	mpz_set(r, n);
	//

	gmp_randstate_t rs;
	gmp_randinit_default(rs);

	mpz_t range;
	mpz_init(range);
	mpz_sub_ui(range, p, 2); // upper range p-2 for finding random "a"

	mpz_t q;
	mpz_init(q);
	mpz_sub_ui(q, p, 1); //q=p-1

	mpz_t a;
	mpz_init(a);

	mpz_t z;
	mpz_init(z);

	for (int i = 1; i <= s; i++) //for i=1 to s
	{

		mpz_urandomm(a, rs, range); // generating random "a"
		mpz_powm(z, a, n, p);				// z=(a^r)mod p

		if (mpz_cmp_ui(z, 1) != 0 && mpz_cmp(z, q) != 0) //if z≠1 and z≠p-1
		{
			for (int j = 1; j <= u - 1; j++) //for j=1 to u-1
			{
				mpz_powm_ui(z, z, 2, p); //z=(z^2)mod
				if (mpz_cmp(z, q) == 0) // if z=-1 return p is likely prime
				{
					return true;
				}
				if (mpz_cmp_ui(z, 1) == 0) //if z≠1 return p is composite
				{
					return false;
				}
			}
			if (mpz_cmp(z, q) != 0) //if z≠p-1 return p is composite
			{
				return false;
			}
		}
	}
	return res = true;
}

int main()
{
	mpz_t p;
	mpz_init(p);
	printf("Enter prime candidate p: ");
	gmp_scanf("%Zd", p);

	int s = 200; //security parameter
	//printf("Enter security parameter s : ");
	//scanf("%d", &s);


	double prob = pow((double)0.25, s);

	if (Rabin_Miller_Test(p, s))
	{
		__gmp_printf("%Zd is likely prime with probability %le\n", p, prob);
	}
	else
	{
		__gmp_printf("%Zd is composite with probability %le\n", p, prob);
	}
}