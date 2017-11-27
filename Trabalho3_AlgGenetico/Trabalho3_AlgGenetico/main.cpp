/*
Algoritmo gen�tico para resolver o problema do caixeiro viajante
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NR_CIDADES    5
#define NR_GERACOES   1000
#define GENES         NR_CIDADES
#define NR_IND_POP    10
#define PMUT          30        // 30%
#define PREC          100       // 100%


/*
Tipos de dados
*/
typedef unsigned int u_int;

typedef struct individuo
{
	u_int id;
	int id_cidade; //1 a 5
	float fitness;
	u_int cromossomo[GENES];
} ind_t;

typedef struct filhos
{
	ind_t filhos[2];
} filhos_t;

/*
Estrutura de dados
*/
u_int distancias[NR_CIDADES][NR_CIDADES] =
{
	{ 0, 50, 30, 50, 20 },
	{ 50, 0, 60, 60, 20 },
	{ 30, 80, 0, 40, 20 },
	{ 60, 60, 40, 0, 20 },
	{ 20, 20, 20, 20, 0 }
};
ind_t populacao[NR_IND_POP]; //Gerado Aleatoriamente
filhos_t melhores[NR_CIDADES];



/*
Cabeçalho das fun��es auxiliares
*/
void cria_populacao_inicial();
void calcula_fitness(ind_t *individuo);
void calcula_fitness_pop();
void  seleciona_melhor();
filhos_t cruzamento(ind_t ind_1, ind_t ind_2);
void mutacao(ind_t *individuo);
void mostra_cromossomo(ind_t individuo);
void mostra_populacao();
void mostra_melhores();
void ordena_pop_fitness();


/*
Fun��o principal
*/
int main()
{
	int geracoes = 0, i, reiniciar = 0, opcaoSub;

	// Gera a sementinha do mal
	srand(time(NULL));

	// Cria uma populacao de individuos
	cria_populacao_inicial();

	do
	{
		// Avalia os individuos (calcula fitness)
		calcula_fitness_pop();

		// Ordena a populacao
		ordena_pop_fitness();

		// Seleciona os x melhores
		seleciona_melhor();

		// Muta alguns individuos (prob. p)
		for (i = 0; i < NR_IND_POP; i++)
		{
			mutacao(&populacao[i]);
		}
		geracoes++;
	} while (geracoes <= NR_GERACOES);

	while (reiniciar != 1)
	{
		printf("\n*******************************************");
		printf("\n1 - Mostra Populacao");
		printf("\n2 - Mostra Melhores");
		printf("\nOpcao? ");
		scanf("%i", &opcaoSub);
		switch (opcaoSub)
		{
		case 1:
			mostra_populacao();
			break;
		case 2:
			mostra_melhores();
			break;
		}
	}
	system("pause");
	return 0;
}

/*
Implementa��o das fun��es auxiliares
*/

void cria_populacao_inicial()
{
	int i, j;
	for (i = 0; i < NR_IND_POP; i++)
	{
		populacao[i].id = i + 1;
		populacao[i].fitness = 0.0;
		for (j = 0; j < GENES; j++)
		{
			populacao[i].cromossomo[j] = rand() % NR_CIDADES;
		}
	}
}

void calcula_fitness(ind_t *individuo)
{
	int i;

	for (i = 0; i < GENES - 1; i++)
	{
		individuo->fitness += abs(individuo->cromossomo[i] - individuo->cromossomo[i + 1]);
	}
}

void calcula_fitness_pop()
{
	int i;

	for (i = 0; i < NR_IND_POP; i++)
	{
		calcula_fitness(&populacao[i]);
	}
}

filhos_t cruzamento(ind_t ind_1, ind_t ind_2)
{
	int ponto_cruzamento = rand() % (NR_CIDADES - 1);
	int gene, i, j;
	filhos_t filhos;

	// Inverte os genes de ind_1 com ind_2
	for (i = 0; i <= ponto_cruzamento; i++)
	{
		gene = ind_1.cromossomo[i];
		ind_1.cromossomo[i] = ind_2.cromossomo[i];
		ind_2.cromossomo[i] = gene;
	}

	// Gera os filhos
	filhos.filhos[0] = ind_1;
	filhos.filhos[1] = ind_2;

	return filhos;
}

void mutacao(ind_t *individuo)
{
	int pmut = rand() % 100;

	if (pmut >= PMUT)
	{
		// Escolhe o ponto de muta��o
		int ponto_de_mutacao = rand() % GENES;  // 0 .. GENES - 1
		individuo->cromossomo[ponto_de_mutacao] = rand() % NR_CIDADES + 1;
	}
}

void mostra_cromossomo(ind_t individuo)
{
	int i;

	printf("Cromossomo do individuo %d\n", individuo.id);
	for (i = 0; i < GENES; i++)
	{
		printf("%d ", individuo.cromossomo[i]);
	}
	printf("Fitness: %.2f\n\n", individuo.fitness);
}

void mostra_populacao()
{
	int i;
	float media_fitness = 0.0;

	printf("Populacao...........\n");
	for (i = 0; i < NR_IND_POP; i++)
	{
		mostra_cromossomo(populacao[i]);
		media_fitness += populacao[i].fitness;
	}
	printf("Media de fitness da populacao: %.2f\n", media_fitness / NR_IND_POP);
}

void ordena_pop_fitness()
{
	int i, j;
	ind_t ind;

	for (i = 0; i < NR_IND_POP; i++)
	{
		for (j = 0; j < NR_IND_POP; j++)
		{
			if (populacao[i].fitness < populacao[j].fitness)
			{
				ind = populacao[i];
				populacao[i] = populacao[j];
				populacao[j] = ind;
			}
		}
	}
}

void seleciona_melhor()
{
	int i;
	for (i = 0; i < NR_CIDADES - 1; i++)
	{
		melhores[i] = cruzamento(populacao[i], populacao[i + 1]);
	}
}

void mostra_melhores()
{
	int i, j, somaDistancia = 0;

	printf("\nMelhores");
	for (i = 0; i < NR_CIDADES; i++)
	{
		printf("\n Individuo: %d - Cidade - Fitness: %f", melhores[i].filhos->id, melhores[i].filhos->fitness);

		somaDistancia = somaDistancia + (distancias[melhores[i].filhos->id][melhores[i].filhos->id + 1]);
	}
	printf("\n Soma das Distancias: %i", somaDistancia);
}
