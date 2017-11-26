#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// e^x para 20 termos
int fatorial( int n )
{
if ( n <= 1 )
return 1;
else
return  n*fatorial(n-1);
}

double taylor_ex (int n_term, double x)
{
if (n_term <= 1)
return 1;
else
return taylor_ex(n_term-1, x) + pow(x, n_term-1)/fatorial(n_term-1);
}

int main()

{
double y,x=2;
y = taylor_ex(20,x);
printf("taylor eh %f\n", y);
return 0;
}

