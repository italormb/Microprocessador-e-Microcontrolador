#include <stdio.h>
unsigned int Raiz_Quadrada(unsigned int s)
{
    unsigned int x=1,p=s;
    while(p>0){
    p-=1;
    x=(((s/x)+x)/2);
    }
    return x;
}

main(){
    unsigned int s=0,x;
    printf("Digite o numero para tirar raiz:\n");
    scanf("%d",&s);
    x=Raiz_Quadrada(s);
    printf("%d\n",x);
}

