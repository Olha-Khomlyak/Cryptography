#include <stdio.h>
#include <gmp.h>
#include <time.h>

int main()
{
	mpz_t n;
	mpz_init(n);
	
	printf("Enter n: ");
	gmp_scanf("%Zd", n);

	mpz_t z;
	mpz_init(z);

	if (mpz_cmp_ui(n, 1) == 0)
	{
		printf("No prime divisor for 1\n");
		return 0;
	}

	mpz_t x;
	mpz_init(x);
	printf("Enter x: ");
	gmp_scanf("%Zd", x);

	mpz_t y;
	mpz_init(y);

	mpz_t y1;
	mpz_init(y1);

	mpz_t c;
	mpz_init(c);
	printf("Enter c: ");
	gmp_scanf("%Zd", c);

	mpz_t r;
	mpz_init(r);
	mpz_t s;
	mpz_init(s);

	//gmp_randstate_t rs; //uncomment to generate random x and c
	//gmp_randinit_default(rs); ////uncomment to generate random x and c

	mpz_t sub;
	mpz_init(sub);

	//mpz_urandomm(x, rs, n); //generating random x
	//gmp_printf("random x= %Zd\n", x);

	mpz_set(y, x);

	//mpz_urandomm(c, rs, n);
	//gmp_printf("random c= %Zd\n", c); //generating random c

	mpz_t d;
	mpz_init(d);
	mpz_set_ui(d, 1);

	mpz_t d1;
	mpz_init(d1);
	mpz_set_ui(d1, 1);

	clock_t t;
	t = clock();

	//f(x)=x^2+1(mod n)

	while (mpz_cmp_ui(d1, 1) == 0)
	{
		mpz_pow_ui(x, x, 2); //x=x^2
		mpz_add(x, x, c);   //x=x^2 + c
		mpz_mod(x, x, n);		//x=x^2+c(mod n)
		mpz_pow_ui(y1, y, 2);//y=y^2 				-
		mpz_add(y, y1, c);//y=y+c							- y=f(x)
		mpz_mod(y1, y, n);//y=y^2+c(mod n)	-
		
		mpz_pow_ui(y, y1, 2); //y=y^2						-
		mpz_add(y1, y, c);		//y1=y^2+c					- y=f(f(x))
		mpz_mod(y, y1, n);		//y=y^2+c(mod n)	-
		mpz_set(y1, y);
		mpz_sub(sub, x, y); //sub=x-y
		mpz_abs(s, sub); // s=|sub|
		mpz_gcd(d, s, n); // d=gcd(x-y,n)
		mpz_set(d1, d);

		if (mpz_cmp(d, n) == 0)
		{
			printf("Failure!");
			return 0;
		}
	}
		gmp_printf("The nontrivial factor of %Zd is %Zd\n",n, d1);
	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds

	printf("Timing: %f seconds \n", time_taken);
	return 0;
}