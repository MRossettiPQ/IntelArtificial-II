// Template.c : Define o ponto de entrada para a aplicação de console.
//

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>

#define ENTRADAS    3
#define SAIDAS      2
#define NR_AMOSTRAS 8
#define EPOCAS      1
#define TX_APR      0.7

int dados_treinamento[NR_AMOSTRAS][ENTRADAS + SAIDAS] = { { 0, 0, 0, 0, 0 },
														  { 0, 0, 1, 0, 1 },
														  { 0, 1, 0, 1, 0 },
														  { 0, 1, 1, 1, 1 }, 
														  { 1, 0, 0, 0, 0 },
														  { 1, 0, 1, 0, 1 },
														  { 1, 1, 0, 1, 0 },
														  { 1, 1, 1, 1, 1 } };

float pesos_sinapticos[SAIDAS][ENTRADAS + 1] = { { 0, 0, 0, 0 },
												 { 0, 0, 0, 0 } }; //W

//Funções auxiliares
int		erro_1																		(int desejado, int saida);
int		erro_2																		(int desejado, int saida);
int		f_degrau																	(float saida);
float	calcular_net_1																();
float	calcular_net_2																();
void	mostrar_pesos_sinapticos													(int entradas[3]);
int		calcular_saida																(float net);
void	treinar_RNA																	();
void	ajustar_pesos_sinapticos													(int entradas[3], int erro, int indice);

int main()
{
	int entradas[3];

	do
	{
		printf("Entrada 1: ");
			scanf("%d", &entradas[0]);
		printf("Entrada 2: ");
			scanf("%d", &entradas[1]);
		printf("Entrada 3: ");
			scanf("%d", &entradas[2]);

		//TREINA A REDE
		treinar_RNA();

		//MOSTRA OS PESOS SINAPTICOS
		mostrar_pesos_sinapticos(entradas);
	
		//USAR RNA
		printf("SAIDA 1 DA RNA: %d\n", calcular_saida(calcular_net_1(entradas)));
		printf("SAIDA 2 DA RNA: %d\n", calcular_saida(calcular_net_2(entradas)));
	} while ((entradas[0] != -100) && (entradas[1] != -100) && (entradas[2] != -100));

	system("pause");
	return 0;
}

int erro_1(int desejado, int saida)
{
	return desejado - saida;
}

int erro_2(int desejado, int saida)
{
	return desejado - saida;
}

int f_degrau(float saida)
{
	if (saida > 0) return 1;
	return 0;
}

float calcular_net_1(int entradas[3])
{
	float net = 0;
	//Para Biaz
	net = pesos_sinapticos[0][0] * 1;
	//Para entrada 1
	net += pesos_sinapticos[0][1] * entradas[0];
	//Para entrada 2
	net += pesos_sinapticos[0][2] * entradas[1];
	//Para entrada 3
	net += pesos_sinapticos[0][3] * entradas[2];

	return net;
}

float calcular_net_2(int entradas[3])
{
	float net = 0;
	//Para Biaz
	net = pesos_sinapticos[1][0] * 1;
	//Para entrada 1
	net += pesos_sinapticos[1][1] * entradas[0];
	//Para entrada 2
	net += pesos_sinapticos[1][2] * entradas[1];
	//Para entrada 3
	net += pesos_sinapticos[1][3] * entradas[2];

	return net;
}

void mostrar_pesos_sinapticos()
{
	int i, j;

	for (i = 0; i < SAIDAS; i++)
	{
		for (j = 0; j < ENTRADAS + 1; j++)
		{
			printf("w[%d][%d]: %.2f\n", i, j, pesos_sinapticos[i][j]);
		}
	}
}

int calcular_saida(float net)
{
	return f_degrau(net);
}

void treinar_RNA()
{
	int i , j, entradas[3], vlr_erro_1, vlr_erro_2, Saida1, Saida2;
	
	for (i = 0; i < EPOCAS; i++)
	{
		for(j = 0; j < NR_AMOSTRAS; j++)
		{
			entradas[0] = dados_treinamento[j][0];
			entradas[1] = dados_treinamento[j][1];
			entradas[2] = dados_treinamento[j][2];
			
			//CALCULAR SAIDA
			Saida1 = calcular_saida(calcular_net_1(entradas));
			Saida2 = calcular_saida(calcular_net_2(entradas));
			
			//VERIFICAÇÃO ERRO
			vlr_erro_1 = erro_1(dados_treinamento[j][3], Saida1);
			vlr_erro_2 = erro_2(dados_treinamento[j][3], Saida2);
			
			if (vlr_erro_1 && vlr_erro_2)
			{
				//Ajusta pesos sinapticos
				ajustar_pesos_sinapticos(entradas, vlr_erro_1, 0);
				ajustar_pesos_sinapticos(entradas, vlr_erro_2, 1);
			}
		}
	}
}

void ajustar_pesos_sinapticos(int entradas[3], int erro, int indice)
{
	int i;

	//Para a biaz
	pesos_sinapticos[indice][0] = pesos_sinapticos[indice][0] + TX_APR * erro * 1;

	for (i = 1; i < ENTRADAS + 1; i++)
	{
		pesos_sinapticos[indice][i] = pesos_sinapticos[indice][i] + TX_APR * erro * entradas[i - 1];
	}
}