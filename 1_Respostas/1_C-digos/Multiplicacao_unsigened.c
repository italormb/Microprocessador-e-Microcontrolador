#include <stdio.h>

int MULT_unsigned(int a, int b)
{
if(b==0) return 0;
else
return (a+MULT_unsigned(a, b-1));
}
int MULT_signed(int a, int b)
{
	if(a<0 && b<0)
	{	a = -a;
		b = -b;
		return MULT_unsigned(a,b);
	}
	else if (a<0 && b>0)
	{	a = -a;
		return -(MULT_unsigned(a,b));
	}
	else if (a>0 && b<0)
	{	b = -b;
		return -(MULT_unsigned(a,b));
	}
	else
	{	return MULT_unsigned(a,b);
	}

}
int Potencia(int x, int     N){

    if(N==0) return 1;
    else   return(MULT_signed(x,Potencia(x,N-1)));
}

int main(){
    int N,x,resultado=0;
    printf("Escreva os fatores do produto:\n");
    scanf("%d\n%d",&x,&N);
    resultado=Potencia(x,N);

    printf("%d\n",resultado);
}
