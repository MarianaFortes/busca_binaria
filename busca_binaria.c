#include <stdio.h>
#include <string.h>
#include <locale.h>

struct _Endereco
{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};
typedef struct _Endereco Endereco;


int main(int argc, char**argv)
{
    FILE *f;
    Endereco e;
    int  i;
    long posicao, inicio, fim, meio;

    if(argc != 2)
    {
        fprintf(stderr, "USO: %s [CEP]", argv[0]);
        return 1;
    }
    f = fopen("cep_ordenado.dat","r");
    fseek(f,0,SEEK_END);
    posicao = ftell(f);
    rewind(f);

    inicio = 0;
    fim = (posicao/sizeof(Endereco))-1;
    i = 0;

	while(inicio <= fim)
	{
		i++;
        meio = (inicio+fim)/2;
        fseek(f, meio * sizeof(Endereco), SEEK_SET);
        fread(&e,sizeof(Endereco),1,f);
        if(strncmp(argv[1],e.cep,8)==0)
        {
			printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep, setlocale(LC_ALL, "portuguese"));
			break;
		}
        else
            if(strncmp(argv[1],e.cep,8) > 0)
				inicio = meio + 1;
            else
                fim = meio - 1;
	}
	printf("\nNumero de buscas: %d", i);
	fclose(f);
}
