#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ENTRADAS        6
#define SAIDAS          1
#define NR_AMOSTRAS     26
#define NR_NEURON_O     8
#define EPOCAS          10000
#define TX_APRENDIZADO  1
#define MOMENTUM        0.3
#define ZERO_TEST       0


/*
Dados para o treinamento da rede
*/
double cj_treinamento[NR_AMOSTRAS][ENTRADAS + SAIDAS] = { { 1, 0, 0, 0, 0, 0, 0.65 }, //A
{ 1, 0, 1, 0, 0, 0, 0.66 }, //B
{ 1, 1, 0, 0, 0, 0, 0.67 }, //C
{ 1, 1, 0, 1, 0, 0, 0.68 }, //D
{ 1, 0, 0, 1, 0, 0, 0.69 }, //E
{ 1, 1, 1, 0, 0, 0, 0.70 }, //F
{ 1, 1, 1, 1, 0, 0, 0.71 }, //G
{ 1, 0, 1, 1, 0, 0, 0.72 }, //H
{ 0, 1, 1, 0, 0, 0, 0.73 }, //I
{ 0, 1, 1, 1, 0, 0, 0.74 }, //J
{ 1, 0, 0, 0, 1, 0, 0.75 }, //K
{ 1, 0, 1, 0, 1, 0, 0.74 }, //L
{ 1, 1, 0, 0, 1, 0, 0.77 }, //M
{ 1, 1, 0, 1, 1, 0, 0.78 }, //N
{ 1, 0, 0, 1, 1, 0, 0.79 }, //O
{ 1, 1, 1, 0, 1, 0, 0.80 }, //P
{ 1, 1, 1, 1, 1, 0, 0.81 }, //Q
{ 1, 0, 1, 1, 1, 0, 0.82 }, //R
{ 0, 1, 1, 0, 1, 0, 0.83 }, //S
{ 0, 1, 1, 1, 1, 0, 0.84 }, //T
{ 1, 0, 0, 0, 1, 1, 0.85 }, //U
{ 1, 0, 1, 0, 1, 1, 0.86 }, //V
{ 0, 1, 1, 1, 0, 1, 0.87 }, //W
{ 1, 1, 0, 0, 1, 1, 0.88 }, //X
{ 1, 1, 0, 1, 1, 1, 0.89 }, //Y
{ 1, 0, 0, 1, 1, 1, 0.90 } };//Z

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
void calcular_delta_saida(double desejado);
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

		inicializa_sinapses();
		treinar_RNA();
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
					resposta = saida_s[cont] * 100;
					printf("\nResposta %i (em numero): %i\n", cont + 1, resposta);
					printf("\nResposta %i (em letras): %c\n", cont + 1, resposta);
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
	int i, j, k;
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
			calcular_delta_saida(cj_treinamento[j][6]);
			calcular_gradiente_oculta();
			calcular_delta_oculta();
			ajustar_pesos_sinapticos(entradas);
		}

	}
	// Mostra media dos erros
	printf("RNA TREINADA - Media dos erros: %lf\n", media_erro);
}

double calcular_erro(double desejado, double saida)
{
	return desejado - saida;
}

void calcular_delta_saida(double desejado)
{
	int i;
	for (i = 0; i < SAIDAS; i++)
	{
		delta_saida[i] = calcular_erro(desejado, saida_s[i]) * (1 - saida_s[i] * saida_s[i]);
	}
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