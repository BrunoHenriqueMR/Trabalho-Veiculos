#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include <string.h>

struct carros
{
	char marca[20];
	char modelo[60];
	char cor[20];
	char placa[20];
	char ano[4];
	char status;
};

int tamanho(FILE *);
void cadastrar(FILE *); // Fun��o de cadastro de ve�culos novos
void consultar(FILE *); // Fun��o de consulta de ve�culo cadastrado
void gerar_arq(FILE *); // Fun��o para arquivar em txt
void excluir(FILE *); // Fun��o para excluir determinado registro

int main()
{
	
	setlocale(LC_ALL,"");
	int decisao,contador=0;
	FILE *arq;
	
	//system("md E:\\Cadastro\\Banco_de_dados");
	if ((arq = fopen("Bdados.dat","rb+")) == NULL)
	{
		if ((arq = fopen("Bdados.dat","wb+")) == NULL)
		{
			printf("Falha ao carregar o arquivo.... Por favor, tente novamente.\n");
			system("pause");
		}
	}
		
	do
	{
		system("CLS");
		printf("=============================================================================================================\n");
		printf(">>>>                            Bem vindo ao banco de dados da (LR) Ve�culos.                            <<<<\n");
		fflush(stdin);
		printf("\nVe�culos cadastrados: %i\n", tamanho(arq));
		printf("=============================================================================================================\n");
		printf("( 1 ) - Cadastrar novo ve�culo.  \n");
		printf("( 2 ) - Consultar ve�culo.  \n");
		printf("( 3 ) - Gerar arquivo (.txt).  \n");
		printf("( 4 ) - Excluir ve�culo.  \n");
		printf("( 5 ) - Sair.  \n");
		printf("=============================================================================================================\n");
		printf("\n Qual sua op��o: ");
		scanf("%d",&decisao);
		
		switch(decisao)
		{
			// Cadastro de ve�culos
			case 1:
				cadastrar(arq);
			break;
			// Consulta de ve�culos
			case 2:
				consultar(arq);
			break;
			// Gerar arquivo
			case 3:
				gerar_arq(arq);
			break;	
			// Exclus�o de ve�culos	
			case 4:
				excluir(arq);
			break;
			case 5: fclose(arq);
		}
		system("Pause");
		
	}while(decisao!=5);
}

// Fun��o de cadastro do novo ve�culo
void cadastrar(FILE *arq)
{
	carros cadastro;
	char verif;
	cadastro.status = ' ';
	//int contador = 0;
	
	fflush(stdin);
	printf("\n\n----- Informe os dados abaixo -----\n\n");
	printf("T�tulo de la�amento n�mero..: %i\n",tamanho(arq));
	printf("Marca do ve�culo............: ");
	gets(cadastro.marca);
	printf("Modelo do ve�culo...........: ");
	gets(cadastro.modelo);
	printf("Cor do ve�culo..............: ");
	gets(cadastro.cor);
	printf("Placa do ve�culo............: ");
	gets(cadastro.placa);
	printf("Ano do ve�culo..............: ");
	gets(cadastro.ano);
	printf("Salvar as informa��es? <S/N>: ");
	scanf("%c%*c",&verif);
	
	if (toupper(verif) == 'S')
	{
		cadastro.status = 'A';
		printf("\n Salvando suas informa��es, por favor, aguarde ....\n");
		fseek(arq, 0, SEEK_END); // posiciona o cursor no fim do arquivo
		fwrite(&cadastro, sizeof(carros), 1, arq);
	}
}

void consultar(FILE *arq)
{
	carros cadastro;
	int titulo;
	
	printf("\n\n----- Informe os dados abaixo -----\n\n");
	printf("Informe o t�tulo de lan�amento..:");
	scanf("%i",&titulo);
	
	if ((titulo <= tamanho(arq)) and (titulo>0))
	{
		fflush(stdin);
		fseek(arq,(titulo-1)*sizeof(carros),SEEK_SET);
		fread(&cadastro,sizeof(carros),1,arq);
		if(cadastro.status == 'A'){
			printf("Marca do ve�culo............: %s\n",cadastro.marca);
			printf("Modelo do ve�culo...........: %s\n",cadastro.modelo);
			printf("Cor do ve�culo..............: %s\n",cadastro.cor);
			printf("Placa do ve�culo............: %s\n",cadastro.placa);
			printf("Ano do ve�culo..............: %s\n",cadastro.ano);	
			//printf("Status do ve�culo..............: %s\n",cadastro.status);	
		}
		else{
			printf("\nRegistro excluido! \n");
		}		
	}
	else
	{
		printf("\nNenhum dado foi encontrado, por favor, tente novamente");
	}
}


void gerar_arq(FILE * arq)
{
	char nomeArq[20];
	printf("Informe o nome do arquivo: ");
	scanf("%s",&nomeArq);
	strcat(nomeArq,".txt");
	
	FILE *arqtxt = fopen(nomeArq,"w");
	
	if (!arqtxt)
	{
		printf("\nN�o foi poss�vel criar este arquivo!\n");
		system("pause");
		
	}
	
	fprintf(arqtxt,"Marca               Modelo               Cor               Placa               Ano               Status");
	fprintf(arqtxt,"\n=======================================================================================================\n");
	
	int nr;
	
	carros cadastro;
	
	for(nr = 0; nr < tamanho(arq); nr++)
	{
		fseek(arq,nr * sizeof(carros),SEEK_SET);
		fread(&cadastro,sizeof(carros),1,arq);
		fprintf(arqtxt,"%-20s %-20s %-20s %-20s %-20s\n",cadastro.marca,cadastro.modelo,cadastro.cor,cadastro.placa,cadastro.ano,cadastro.status);
		
	}
	fprintf(arqtxt,"\n=========================================================================================================");
	fclose(arqtxt);
}

void excluir(FILE *arq)
{
	carros cadastro;
	char confirma;
	int titulo;
	int contador = 0;

	printf("\nInforme o codigo do registro para excluir\n");
	scanf("%d", &titulo);
	if ((titulo <= tamanho(arq)) && (titulo>0))
	{
		fseek(arq, (titulo - 1) * sizeof(carros), SEEK_SET);
		fread(&cadastro, sizeof(carros), 1, arq);
		if (cadastro.status == 'A')
		{
			printf("\nMarca do ve�culo....:%s", cadastro.marca);
			printf("\nModelo do ve�culo...:%s", cadastro.modelo);
			printf("\nCor do ve�culo......:%s", cadastro.cor);
			printf("\nPlaca do ve�culo....:%s", cadastro.placa);
			printf("\nAno do ve�culo......:%s", cadastro.ano);
			//printf("\nStatus do ve�culo......:%s", cadastro.status);			
			printf("\nConfirma a exclusao: <s/n>\n");
			getchar();
			scanf("%c", &confirma);

			if (toupper(confirma) == 'S')
			{
				printf("\nexcluindo...\n\n");
				cadastro.status = 'E';
				fseek(arq, (titulo - 1) * sizeof(carros), SEEK_SET);
				fwrite(&cadastro, sizeof(carros), 1, arq);
				tamanho - 1;
			}
		}
	else
		printf("Registro inexistente! \n");
	}
	else
	{
		printf("\nNumero de registro invalido!\n");
	}
	system("pause");
}


int tamanho(FILE *arq)
{
	fseek(arq, 0, SEEK_END);
	return ftell(arq) / sizeof(carros);
}



