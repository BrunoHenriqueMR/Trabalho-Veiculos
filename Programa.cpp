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
void cadastrar(FILE *); // Função de cadastro de veículos novos
void consultar(FILE *); // Função de consulta de veículo cadastrado
void gerar_arq(FILE *); // Função para arquivar em txt
void excluir(FILE *); // Função para excluir determinado registro

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
		printf(">>>>                            Bem vindo ao banco de dados da (LR) Veículos.                            <<<<\n");
		fflush(stdin);
		printf("\nVeículos cadastrados: %i\n", tamanho(arq));
		printf("=============================================================================================================\n");
		printf("( 1 ) - Cadastrar novo veículo.  \n");
		printf("( 2 ) - Consultar veículo.  \n");
		printf("( 3 ) - Gerar arquivo (.txt).  \n");
		printf("( 4 ) - Excluir veículo.  \n");
		printf("( 5 ) - Sair.  \n");
		printf("=============================================================================================================\n");
		printf("\n Qual sua opção: ");
		scanf("%d",&decisao);
		
		switch(decisao)
		{
			// Cadastro de veículos
			case 1:
				cadastrar(arq);
			break;
			// Consulta de veículos
			case 2:
				consultar(arq);
			break;
			// Gerar arquivo
			case 3:
				gerar_arq(arq);
			break;	
			// Exclusão de veículos	
			case 4:
				excluir(arq);
			break;
			case 5: fclose(arq);
		}
		system("Pause");
		
	}while(decisao!=5);
}

// Função de cadastro do novo veículo
void cadastrar(FILE *arq)
{
	carros cadastro;
	char verif;
	cadastro.status = ' ';
	//int contador = 0;
	
	fflush(stdin);
	printf("\n\n----- Informe os dados abaixo -----\n\n");
	printf("Título de laçamento número..: %i\n",tamanho(arq));
	printf("Marca do veículo............: ");
	gets(cadastro.marca);
	printf("Modelo do veículo...........: ");
	gets(cadastro.modelo);
	printf("Cor do veículo..............: ");
	gets(cadastro.cor);
	printf("Placa do veículo............: ");
	gets(cadastro.placa);
	printf("Ano do veículo..............: ");
	gets(cadastro.ano);
	printf("Salvar as informações? <S/N>: ");
	scanf("%c%*c",&verif);
	
	if (toupper(verif) == 'S')
	{
		cadastro.status = 'A';
		printf("\n Salvando suas informações, por favor, aguarde ....\n");
		fseek(arq, 0, SEEK_END); // posiciona o cursor no fim do arquivo
		fwrite(&cadastro, sizeof(carros), 1, arq);
	}
}

void consultar(FILE *arq)
{
	carros cadastro;
	int titulo;
	
	printf("\n\n----- Informe os dados abaixo -----\n\n");
	printf("Informe o título de lançamento..:");
	scanf("%i",&titulo);
	
	if ((titulo <= tamanho(arq)) and (titulo>0))
	{
		fflush(stdin);
		fseek(arq,(titulo-1)*sizeof(carros),SEEK_SET);
		fread(&cadastro,sizeof(carros),1,arq);
		if(cadastro.status == 'A'){
			printf("Marca do veículo............: %s\n",cadastro.marca);
			printf("Modelo do veículo...........: %s\n",cadastro.modelo);
			printf("Cor do veículo..............: %s\n",cadastro.cor);
			printf("Placa do veículo............: %s\n",cadastro.placa);
			printf("Ano do veículo..............: %s\n",cadastro.ano);	
			//printf("Status do veículo..............: %s\n",cadastro.status);	
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
		printf("\nNão foi possível criar este arquivo!\n");
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
			printf("\nMarca do veículo....:%s", cadastro.marca);
			printf("\nModelo do veículo...:%s", cadastro.modelo);
			printf("\nCor do veículo......:%s", cadastro.cor);
			printf("\nPlaca do veículo....:%s", cadastro.placa);
			printf("\nAno do veículo......:%s", cadastro.ano);
			//printf("\nStatus do veículo......:%s", cadastro.status);			
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



