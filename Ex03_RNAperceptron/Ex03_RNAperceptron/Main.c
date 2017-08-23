// Template.c : Define o ponto de entrada para a aplicação de console.
//

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>

#define ENTRADAS    2
#define SAIDAS      1
#define NR_AMOSTRAS 4
#define EPOCAS      1000
#define TX_APR      0.7

int dados_treinamento[NR_AMOSTRAS][ENTRADAS + SAIDAS] = { { 0, 0, 0 },
														{ 0, 1, 0 },
														{ 1, 0, 0 },
														{ 1, 1, 1 } };

float pesos_sinapticos[ENTRADAS + 1] = { 0, 0, 0 }; //W

//Funções auxiliares
int		erro																		(int desejado, int saida);
int		f_degrau																	(float saida);
float	calcular_net																();
void	mostrar_pesos_sinapticos													(int entradas[2]);
int		calcular_saida																(float net);
void	treinar_RNA																	();
void	ajustar_pesos_sinapticos													(int entradas[2], int erro);

int main()
{
	int entradas[2];

	do
	{
		printf("Entrada 1: ");
			scanf("%d", &entradas[0]);
		printf("Entrada 2: ");
			scanf("%d", &entradas[1]);
		//TREINA A REDE
		treinar_RNA();

		//MOSTRA OS PESOS SINAPTICOS
		mostrar_pesos_sinapticos(entradas);
	
		//USAR RNA
		printf("SAIDAS DA RNA: %d\n", calcular_saida(calcular_net(entradas)));
	} while ((entradas[0] != -100) && (entradas[1] != -100));

	system("pause");
	return 0;
}

int erro(int desejado, int saida)
{
	return desejado - saida;
}

int f_degrau(float saida)
{
	if (saida > 0) return 1;
	return 0;
}

float calcular_net(int entradas[2])
{
	float net = 0;
	//Para Biaz
	net = pesos_sinapticos[0] * 1;
	//Para entrada 1
	net += pesos_sinapticos[1] * entradas[0];
	//Para entrada 2
	net += pesos_sinapticos[2] * entradas[1];

	return net;
}

void mostrar_pesos_sinapticos()
{
	int i;

	for (i = 0; i < ENTRADAS + 1; i++)
	{
		printf("w[%d]: %.2f\n", i, pesos_sinapticos[i]);
	}
}

int calcular_saida(float net)
{
	return f_degrau(net);
}

void treinar_RNA()
{
	int i , j, entradas[2], vlr_erro, Saida;
	
	for (i = 0; i < EPOCAS; i++)
	{
		for(j = 0; j < NR_AMOSTRAS; j++)
		{
			entradas[0] = dados_treinamento[j][0];
			entradas[1] = dados_treinamento[j][1];
			//CALCULAR SAIDA
			Saida = calcular_saida(calcular_net(entradas));
			//VERIFICAÇÃO ERRO
			vlr_erro = erro(dados_treinamento[j][2], Saida);
			if (vlr_erro)
			{
				//Ajusta pesos sinapticos
				ajustar_pesos_sinapticos(entradas, vlr_erro);
			}
		}
	}
}

void ajustar_pesos_sinapticos(int entradas[2], int erro)
{
	int i;
	//Para a biaz
	pesos_sinapticos[0] = pesos_sinapticos[0] + TX_APR * erro * 1;

	for (i = 1; i < ENTRADAS + 1; i++)
	{
		pesos_sinapticos[i] = pesos_sinapticos[i] + TX_APR * erro * entradas[i - 1];
	}
}