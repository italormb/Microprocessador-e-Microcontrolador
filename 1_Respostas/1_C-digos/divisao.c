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
int div(int D, int q){
    int i=0,aux=q;
 while(aux < D || aux==D){
    i++;
    aux=aux+q;
    }
    return i;
}

int main(){
    int D,q,d;
    printf("Escreva o Divisor,quociente:\n");
    scanf("%i\n",&D);
    scanf("%i\n",&q);
    d=div(D,q);
    printf("%d\n",d);
}
