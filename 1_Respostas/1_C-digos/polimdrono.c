int Palindromo(int vetor[ ], int tamanho);

int Palindromo(int *p,int tamanho)
{
	int i=0;
	while(i<tamanho)
	{
		if(p[i]!=p[(tamanho-1)-i])
		{
			return 0;
		}
    i++;
	}
	return 1;
}
