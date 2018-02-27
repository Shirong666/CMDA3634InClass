#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "functions.h"

int main (int argc, char **argv) {

	//seed value for the randomizer 
	double seed;

	seed = clock(); //this will make your program run differently everytime
	//seed = 0; //uncomment this and you program will behave the same everytime it's run

	srand48(seed);


	//begin by getting user's input
	unsigned int n;

	printf("Enter a number of bits: ");
	scanf("%u",&n);

	//make sure the input makes sense
	if ((n<2)||(n>30)) {
		printf("Unsupported bit size.\n");
		return 0;  	
	}

	int p;

	/* Q2.2: Use isProbablyPrime and randomXbitInt to find a random n-bit prime number */
	do {
		p = randXbitInt(n);
	}while (!isProbablyPrime(p));
	printf("p = %u is probably prime.\n", p);

	/* Q3.2: Use isProbablyPrime and randomXbitInt to find a new random n-bit prime number 
	   which satisfies p=2*q+1 where q is also prime */
	unsigned  int q;
	unsigned  int flag=0;
	unsigned int randnum = 0;
	while (flag==0 )
	{
		randnum = randXbitInt(n);
		if (isProbablyPrime(randnum)==1)
		{
			unsigned int test = (randnum -1)/2;
			if (isProbablyPrime(test)==1)
			{
				q = test;
				p = randnum;
				flag =1;
			}

		}
	}	



	printf("p = %u is probably prime and equals 2*q + 1. q= %u and is also probably prime.\n", p, q);  

	/* Q3.3: use the fact that p=2*q+1 to quickly find a generator */
	unsigned int g = findGenerator(p);

	printf("g = %u is a generator of Z_%u \n", g, p);  



	unsigned int x=1;
	for (unsigned int k = 0; k<p-2;k++)
	{
		x=x+ rand()%2;
	}
	printf("x = %u is a random num in the range of 1 to p(%u)-1 \n", x,p);	
	unsigned int h;
	h = modExp(g,x,p);
	printf("using h=g to x, we get a h = %u \n", h);
	for (unsigned int d=1; d<p;d++)
	{
		if(modExp(g,d,p)==h)
		{
			printf("knowing g and h and using for loop, we get the x = %u \n", d);
			break;
		}
	}

	return 0;
}
