/* Dados para o treinamento da rede */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ENTRADAS        1
#define SAIDAS          2
#define NR_AMOSTRAS     31
#define NR_NEURON_O     4
#define EPOCAS          100000
#define TX_APRENDIZADO  1
#define MOMENTUM        0.9
#define ZERO_TEST       0


/* Dados para o treinamento da rede */
double cj_treinamento[NR_AMOSTRAS][ENTRADAS + SAIDAS] =
{
	{ 0.05, 0.197, 0.122 }, //5 cm - Baixo
	{ 0.10, 0.172, 0.122 }, //10 cm
	{ 0.11, 0.167, 0.122 }, //11 cm	
	{ 0.20, 0.122, 0.122 }, //20 cm - Equilibrio
	{ 0.21, 0.122, 0.127 }, //21 cm
	{ 0.22, 0.122, 0.132 }, //22 cm
	{ 0.23, 0.122, 0.137 }, //23 cm
	{ 0.12, 0.162, 0.122 }, //12 cm
	{ 0.13, 0.157, 0.122 }, //13 cm	
	{ 0.26, 0.122, 0.152 }, //26 cm
	{ 0.27, 0.122, 0.157 }, //27 cm
	{ 0.30, 0.122, 0.172 }, //30 cm
	{ 0.31, 0.122, 0.177 }, //31 cm
	{ 0.17, 0.137, 0.122 }, //17 cm
	{ 0.18, 0.132, 0.122 }, //18 cm
	{ 0.19, 0.127, 0.122 }, //19 cm
	{ 0.33, 0.122, 0.187 }, //33 cm
	{ 0.28, 0.122, 0.162 }, //28 cm
	{ 0.29, 0.122, 0.167 }, //29 cm
	{ 0.34, 0.122, 0.192 }, //34 cm
	{ 0.24, 0.122, 0.142 }, //24 cm
	{ 0.25, 0.122, 0.147 }, //25 cm	
	{ 0.06, 0.192, 0.122 }, //6 cm
	{ 0.08, 0.182, 0.122 }, //8 cm
	{ 0.09, 0.177, 0.122 }, //9 cm
	{ 0.07, 0.187, 0.122 }, //7 cm	
	{ 0.14, 0.152, 0.122 }, //14 cm
	{ 0.15, 0.147, 0.122 }, //15 cm
	{ 0.16, 0.142, 0.122 }, //16 cm
	{ 0.32, 0.122, 0.182 }, //32 cm
	{ 0.35, 0.122, 0.197 }  //35 cm - Alto
};

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
	int opcao = 0, cont;
	double resposta = 0;
	double entradas[ENTRADAS];


	inicializa_sinapses();
	treinar_RNA();


	while (opcao != 3)
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
				printf("Entrada %i: ", cont + 1);
				scanf("%lf", &entradas[cont]);
				entradas[cont] = entradas[cont] / 100;
			}
			calcular_saidas(entradas);
			for (cont = 0; cont < SAIDAS; cont++)
			{
				resposta = saida_s[cont] * 1000;
				printf("\nResposta %i (Sem Converter): %g\n", cont + 1, saida_s[cont]);
				printf("\nResposta %i (em PWM): %g\n", cont + 1, resposta);
				resposta = 0;
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
	int i;
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