// Perceptron.c : Define o ponto de entrada para a aplicação de console.
//

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>

#define ENTRADAS    3
#define SAIDAS      2
#define NR_AMOSTRAS 8
#define EPOCAS      10000
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
int		erro																		(int desejado, int saida);
int		f_degrau																	(float saida);
float	calcular_net																(int DadosEntradas[ENTRADAS], int indice);
void	mostrar_pesos_sinapticos													(int DadosEntradas[ENTRADAS]);
int		calcular_saida																(float net);
void	treinar_RNA																	();
void	ajustar_pesos_sinapticos													(int DadosEntradas[ENTRADAS], int erro, int indice);

int		main																		()
{
	int cont, DadosEntradas[ENTRADAS];

	do
	{
		for (cont = 0; cont < ENTRADAS; cont++)
		{
			printf("Entrada %i: ", cont);
			scanf("%i", &DadosEntradas[cont]);
		}
		printf("\n");

		//TREINA A REDE
		treinar_RNA();

		//MOSTRA OS PESOS SINAPTICOS
		mostrar_pesos_sinapticos(DadosEntradas);

		//USAR RNA
		for (cont = 0; cont < SAIDAS; cont++)
		{
			printf("SAIDA %i DA RNA: %i\n", cont, calcular_saida(calcular_net(DadosEntradas, cont)));
		}
		printf("==============================================================================\n");
	} while ((DadosEntradas[0] != -100) && (DadosEntradas[1] != -100) && (DadosEntradas[2] != -100));

	system("pause");
	return 0;
}

int		erro																		(int desejado, int saida)
{
	return desejado - saida;
}

float	calcular_net																(int DadosEntradas[ENTRADAS], int indice)
{
	int cont;
	float net = 0;
	//Para Biaz
	net = pesos_sinapticos[indice][0] * 1;
	//Para entrada
	for (cont = 0; cont < ENTRADAS; cont++)
	{
		net += pesos_sinapticos[indice][cont + 1] * DadosEntradas[cont];
	}

	return net;
}

void	mostrar_pesos_sinapticos													()
{
	int i, j;

	for (j = 0; j < SAIDAS; j++)
	{
		for (i = 0; i < (ENTRADAS + 1); i++)
		{
			printf("Pesos Sinapticos[%i][%i]: %.2f\n", j, i, pesos_sinapticos[j][i]);
		}
	}
	printf("\n");
}

int		calcular_saida																(float net)
{
	return f_degrau(net);
}

int		f_degrau																	(float saida)
{
	if (saida > 0)
	{
		return 1;
	}
	return 0;
}

void	treinar_RNA																	()
{
	int i, j, k, vlr_erro[SAIDAS], Saida[SAIDAS], DadosEntradas[ENTRADAS + SAIDAS];

	for (i = 0; i < EPOCAS; i++)
	{
		for (j = 0; j < NR_AMOSTRAS; j++)
		{
			for (k = 0; k < (ENTRADAS + SAIDAS); k++)
			{
				DadosEntradas[k] = dados_treinamento[j][k];
			}

			//CALCULAR SAIDA
			for (k = 0; k < SAIDAS; k++)
			{
				Saida[k] = calcular_saida(calcular_net(DadosEntradas, k));
			}

			//VERIFICAÇÃO ERRO 0 1 2 3 4
			for (k = 0; k < SAIDAS; k++)
			{
				vlr_erro[k] = erro(DadosEntradas[ENTRADAS + k], Saida[k]);
			}
			//Ajusta pesos sinapticos
			if (vlr_erro[0] && vlr_erro[1])
			{
				for (k = 0; k < SAIDAS; k++)
				{
					ajustar_pesos_sinapticos(DadosEntradas, vlr_erro[k], k);
				}
			}
		}
	}
}

void	ajustar_pesos_sinapticos													(int DadosEntradas[ENTRADAS], int erro, int indice)
{
	int i;

	//Para a biaz
	pesos_sinapticos[indice][0] = pesos_sinapticos[indice][0] + TX_APR * erro * 1;

	for (i = 1; i < ENTRADAS + 1; i++)
	{
		pesos_sinapticos[indice][i] = pesos_sinapticos[indice][i] + TX_APR * erro * DadosEntradas[i - 1];
	}
}