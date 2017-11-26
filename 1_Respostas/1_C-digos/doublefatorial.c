#include<stdio.h>

unsigned long long MULT_unsigned(unsigned long long a, unsigned long long b)
{
if(b==0) return 0;
else
return a+MULT_unsigned(a, (b-1));
}

unsigned long long Remainder (unsigned long long dividend,unsigned long long divisor)
{
	while (dividend >= divisor)
	{
		dividend -= divisor;
	}

	return dividend;
}

unsigned long long Duplo_Fatorial (long long n)
{
	if(n==0 || n==1)
	{
		return 1;
	}
	/*Aqui o código verifica se o número é ímpar ou par.*/
	else if(Remainder(n,2)==0)
	{
		/*Se o número for par vai entrar aqui.*/
		/*A função vai retornar n*(n-2) até que n seja igual a zero, onde irá retornar um.*/
		if(n>0)
		{
			return (MULT_unsigned(n,Duplo_Fatorial(n-2)));
		}
		else
		{
			return 1;
		}

	}
	else
	{
		if(n>1)
		{
			return (MULT_unsigned(n,Duplo_Fatorial(n-2)));
		}
		else
		{
			return 1;
		}
	}
}
int main(){
    int n

}
