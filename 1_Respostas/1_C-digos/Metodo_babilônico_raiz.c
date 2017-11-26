#include <stdio.h>

/* retorna a raiz quadrada de s */
float rq(float s);

int main(void)
{
    float s, x;

    while(1) {
       printf("Entre com um numero (>0): ");
       scanf("%f", &s);
       x = rq(s);
       printf("Raiz quadrada de %.2f: x = %.4f\n", s, x);
       printf("(verificacao: x * x = %.4f)\n", x * x);
    }

    return 0;
}

float rq(float s)
{
    /* implemente a função raiz quadrada aqui */
    float x=1;

    while(s>0){

    x=(x+(s/x))/2;

    }
    return x;
}
