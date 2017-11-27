/* Dados para o treinamento da rede */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ENTRADAS        4
#define SAIDAS          1
#define NR_AMOSTRAS     25
#define NR_NEURON_O     8
#define EPOCAS          100000
#define TX_APRENDIZADO  1
#define MOMENTUM        0.9
#define ZERO_TEST       0


/* Dados para o treinamento da rede */
double cj_treinamento[NR_AMOSTRAS][ENTRADAS + SAIDAS] = { { 1, 2, 3, 4, 1 },
{ 5, 6, 7, 8, 2 },
{ 9, 10, 11, 12, 3 },
{ 13, 14, 15, 16, 4 },
{ 17, 18, 19, 20, 5 },
{ 21, 22, 23, 24, 6 },
{ 25, 26, 27, 28, 7 },
{ 29, 30, 31, 32, 8 },
{ 33, 34, 35, 36, 9 },
{ 37, 38, 39, 40, 10 },
{ 41, 42, 43, 44, 11 },
{ 45, 46, 47, 48, 12 },
{ 49, 50, 51, 52, 13 },
{ 53, 54, 55, 56, 14 },
{ 57, 58, 59, 60, 15 },
{ 61, 62, 63, 64, 16 },
{ 65, 66, 67, 68, 17 },
{ 69, 70, 71, 72, 18 },
{ 73, 74, 75, 76, 19 },
{ 77, 78, 79, 80, 20 },
{ 81, 81, 82, 83, 21 },
{ 85, 86, 87, 88, 22 },
{ 89, 90, 91, 92, 23 },
{ 93, 94, 95, 96, 24 },
{ 97, 98, 99, 0, 25 } };

/* Variaveis globais */
double w_e_o[ENTRADAS + 1][NR_NEURON_O];
double w_o_s[NR_NEURON_O + 1][SAIDAS];
double saida_o[NR_NEURON_O];
double saida_s[SAIDAS];
double delta_saida[SAIDAS];
double gradiente_oculta[NR_NEURON_O];
double delta_oculta[NR_NEURON_O];
double media_erro = 0.0;


/* Cabeçalho das funções auxiliares */
void inicializa_sinapses();
int gera_nr_aleatorios();
void mostrar_sinapses();
double f_sigmoid(double net);
void calcular_saidas(double entradas[ENTRADAS]);
void treinar_RNA();
double calcular_erro(double desejado, double saida);
void menu();
void calcular_delta_saida(double desejado, int indice);
void calcular_delta_oculta();
void calcular_gradiente_oculta();
void ajustar_pesos_sinapticos(double entradas[ENTRADAS]);
void gravar_pesos_sinapticos();
void restaurar_pesos_sinapticos();

/* Função principal */
int main()
{
	int opcao = 0, cont, resposta;
	double entradas[ENTRADAS];


	inicializa_sinapses();
	treinar_RNA();

	while (opcao != 4)
	{
		printf("\nRede Neural Perceptron de Multiplas Camadas\n");
		printf("Problema do OU EXCLUSIVO - XOR\n");
		printf("*******************************************\n\n");
		printf("1.Usar a rede\n");
		printf("2.Ver pesos sinapticos\n");
		printf("3.Sair\n");
		printf("Opcao? ");
		scanf("%d", &opcao);

		switch (opcao)
		{
		case 1:
			for (cont = 0; cont < ENTRADAS; cont++)
			{
				printf("Entrada %i: ", cont);
				scanf("%lf", &entradas[cont]);
			}
			calcular_saidas(entradas);
			for (cont = 0; cont < SAIDAS; cont++)
			{
				printf("\nResposta %i (em numero): %i\n", cont + 1, saida_s[cont]);
			}
			break;

		case 2: mostrar_sinapses();
			break;

		case 3: exit(0);
		}
	}
	return 0;
}

void inicializa_sinapses()
{
	int i, j;

	// Inicializa pesos sin�pticos da entrada para a camada oculta
	for (i = 0; i < ENTRADAS + 1; i++)
	{
		for (j = 0; j < NR_NEURON_O; j++)
		{
#if ZERO_TEST
			w_e_o[i][j] = 0.0;
#else
			w_e_o[i][j] = gera_nr_aleatorios();
#endif
		}
	}
	// Inicializa pesos sin�pticos da camada oculta para a sa�da
	for (i = 0; i < NR_NEURON_O + 1; i++)
	{
		for (j = 0; j < SAIDAS; j++)
		{
#if ZERO_TEST
			w_o_s[i][j] = 0.0;
#else
			w_o_s[i][j] = gera_nr_aleatorios();
#endif
		}
	}

}

int gera_nr_aleatorios()
{
	int numeros[2] = { -1, 1 };
	// Retorna -1 ou 1
	return (numeros[rand() % 2]);
}

void mostrar_sinapses()
{
	int i, j;

	// Inicializa pesos sin�pticos da entrada para a camada oculta
	for (i = 0; i < ENTRADAS + 1; i++)
	{
		for (j = 0; j < NR_NEURON_O; j++)
		{
			printf("w_e_o[%d][%d]: %f ", i, j, w_e_o[i][j]);
			printf("\n");
		}
		printf("\n");
	}

	// Inicializa pesos sin�pticos da camada oculta para a sa�da
	for (i = 0; i < NR_NEURON_O + 1; i++)
	{
		for (j = 0; j < SAIDAS; j++)
		{
			printf("w_o_s[%d][%d]: %f ", i, j, w_o_s[i][j]);
			printf("\n");
		}
		printf("\n");
	}
}

double f_sigmoid(double net)
{
	return 1 / (1 + exp(-net));
}

void calcular_saidas(double entradas[ENTRADAS])
{
	int i, j;

	// Calcular os nets da entrada para a camada oculta
	for (i = 0; i < NR_NEURON_O; i++)
	{
		saida_o[i] = 0.0;
		saida_o[i] += w_e_o[0][i] * 1;  // Calcula saida para bias

		for (j = 1; j < ENTRADAS + 1; j++)
		{
			saida_o[i] += w_e_o[j][i] * entradas[j - 1];
		}

		// Calcular a saida de saida_o[i]
		saida_o[i] = f_sigmoid(saida_o[i]);
	}

	// Calcular os nets da camada oculta para a sa�da
	for (i = 0; i < SAIDAS; i++)
	{
		saida_s[i] = 0.0;
		saida_s[i] += w_o_s[0][i] * 1;  // Calcula saida para bias

		for (j = 1; j < NR_NEURON_O + 1; j++)
		{
			saida_s[i] += w_o_s[j][i] * saida_o[j - 1];
		}

		saida_s[i] = f_sigmoid(saida_s[i]);
	}
}

void treinar_RNA()
{
	int i, j, k, l;
	double entradas[ENTRADAS];

	for (i = 1; i <= EPOCAS; i++)
	{

		for (j = 0; j < NR_AMOSTRAS; j++)
		{
			for (k = 0; k < ENTRADAS; k++)
			{
				entradas[k] = cj_treinamento[j][k];
			}

			// Feedforward
			calcular_saidas(entradas);

			// Backward (backpropagation)
			for (l = 0; l < SAIDAS; l++)
			{
				calcular_delta_saida(cj_treinamento[j][k + l], l);
				calcular_gradiente_oculta();
				calcular_delta_oculta();
				ajustar_pesos_sinapticos(entradas);
			}
		}

	}
	// Mostra media dos erros
	printf("RNA TREINADA - Media dos erros: %lf\n", media_erro);
}

double calcular_erro(double desejado, double saida)
{
	return desejado - saida;
}

void calcular_delta_saida(double desejado, int indice)
{
	delta_saida[indice] = calcular_erro(desejado, saida_s[indice]) * (1 - saida_s[indice] * saida_s[indice]);
}

void calcular_gradiente_oculta()
{
	int i, j;

	for (i = 0; i < SAIDAS; i++)
	{
		for (j = 1; j < NR_NEURON_O + 1; j++)
		{
			gradiente_oculta[j - 1] = delta_saida[i] * w_o_s[j][i];
		}
	}
}

void calcular_delta_oculta()
{
	int i;
	for (i = 0; i < NR_NEURON_O; i++)
	{
		delta_oculta[i] = gradiente_oculta[i] * saida_o[i] * (1 - saida_o[i]);
	}
}

void ajustar_pesos_sinapticos(double entradas[ENTRADAS])
{
	int i, j;

	// Ajusta os pesos sin�pticos da camada intermedi�ria para a camada de sa�da
	for (i = 0; i < SAIDAS; i++)
	{
		w_o_s[0][i] = w_o_s[0][i] + TX_APRENDIZADO * delta_saida[i] * 1;
		for (j = 1; j < NR_NEURON_O + 1; j++)
		{
			w_o_s[j][i] = w_o_s[j][i] + TX_APRENDIZADO * delta_saida[i] * saida_o[j - 1];
		}
	}

	// Ajusta os pesos sin�pticos da camada de saida para a camada intermedi�ria
	for (i = 0; i < NR_NEURON_O; i++)
	{
		w_e_o[0][i] = w_e_o[0][i] + TX_APRENDIZADO * delta_oculta[i] * 1;
		for (j = 1; j < ENTRADAS + 1; j++)
		{
			w_e_o[j][i] = w_e_o[j][i] + TX_APRENDIZADO * delta_oculta[i] * entradas[j - 1];
		}
	}
}