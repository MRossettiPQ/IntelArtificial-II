/*
Algoritmo Genético para compor músicas
*/

#include <stdio.h>
#include <stdlib.h>

#define T_CROMOSSOMO        3     // Tamanho do cromossomo
#define T_POPULACAO         12    // Quantidade de individuos na populacao
#define NR_CIDADES          5
#define NR_GERACOES         1000  // Numero de gerações (épocas)
#define NR_IND_SELECIONADOS 6     // Número dos melhores indivíduos para seleção

#define SHOW_POPULATION     1     // Para mostrar ou não os indivídios da população


int cidades[NR_CIDADES]
{ 
	1, 2, 3, 4, 5 
};

int distancias[NR_CIDADES][NR_CIDADES] =
{
	{ 0, 1, 2, 3, 4 },
	{ 1, 0, 1, 2, 3 },
	{ 2, 1, 0, 1, 2 },
	{ 3, 2, 1, 0, 1 },
	{ 4, 3, 2, 1, 0 }
};

typedef struct t_ind 
{
	enum notas cromossomo[T_CROMOSSOMO];
	float fitness;
}individuo;


typedef struct t_pop {
	unsigned int geracao;
	float media_fitness;
	individuo individuos[T_POPULACAO];
}populacao;


void geraPopulacaoInicial(populacao* pop);
individuo geraIndividuo();
float fAvaliacao(individuo ind);
void ordenarPopulacao(individuo *individuos);
void cruzamento(individuo *individuos);
void mutacao(individuo *ind);
void mostrarDadosIndividuo(individuo ind);
void imprimirCromossomo(enum notas *cromossomo);

int main()
{
	populacao popNotasMusicais;
	int i, j;

	srand(time(NULL));

	geraPopulacaoInicial(&popNotasMusicais);

	for (i = 1; i <= NR_GERACOES; i++) {
		for (j = 0; j < T_POPULACAO; j++) {
			popNotasMusicais.individuos[j].fitness = fAvaliacao(popNotasMusicais.individuos[j]);
		#if SHOW_POPULATION
					mostrarDadosIndividuo(popNotasMusicais.individuos[j]);
		#endif
		}
		system("pause");
		ordenarPopulacao(popNotasMusicais.individuos);

		// Cruzar
		cruzamento(popNotasMusicais.individuos);

		// Mutar
		for (j = 0; j < T_POPULACAO; j++) {
			mutacao(&popNotasMusicais.individuos[j]);
		}
	}
	return 0;
}

void geraPopulacaoInicial(populacao* pop)
{
	int i;

	pop->geracao = 0;
	pop->media_fitness = 0;

	for (i = 0; i < T_POPULACAO; i++) 
	{
		pop->individuos[i] = geraIndividuo();
	}
}

individuo geraIndividuo()
{
	individuo ind;
	int i;

	ind.fitness = 0;
	for (i = 0; i < T_CROMOSSOMO; i++)
		ind.cromossomo[i] = rand() % 12;

	return ind;
}

float fAvaliacao(individuo ind)
{
	float fitness = 1;

	fitness += ind.cromossomo[0] == ind.cromossomo[1] ? 0 : 1;
	fitness += ind.cromossomo[0] == ind.cromossomo[2] ? 0 : 1;
	fitness += ind.cromossomo[1] == ind.cromossomo[2] ? 0 : 1;

	return fitness / 4;
}

void ordenarPopulacao(individuo *individuos)
{
	int i, j;
	individuo aux;

	for (i = 0; i < T_POPULACAO; i++) {
		for (j = 0; j < T_POPULACAO - 1; j++) {
			if (individuos[j].fitness < individuos[j + 1].fitness) {
				aux = individuos[j];
				individuos[j] = individuos[j + 1];
				individuos[j + 1] = aux;
			}
		}
	}
}

void cruzamento(individuo *individuos)
{
	int i, j, pontoCruzamento;

	for (i = 0; i < NR_IND_SELECIONADOS; i += 2) {
		pontoCruzamento = rand() % 2 + 1;
		// Primeiro filho
		for (j = 0; j < pontoCruzamento; j++) {
			individuos[NR_IND_SELECIONADOS + i].cromossomo[j] = individuos[i].cromossomo[j];
		}
		for (j = pontoCruzamento; j < T_CROMOSSOMO; j++) {
			individuos[NR_IND_SELECIONADOS + i].cromossomo[j] = individuos[i + 1].cromossomo[j];
		}
		// Segundo filho
		for (j = 0; j < pontoCruzamento; j++) {
			individuos[NR_IND_SELECIONADOS + i + 1].cromossomo[j] = individuos[i + 1].cromossomo[j];
		}
		for (j = pontoCruzamento; j < T_CROMOSSOMO; j++) {
			individuos[NR_IND_SELECIONADOS + i + 1].cromossomo[j] = individuos[i].cromossomo[j];
		}
	}
}

void mutacao(individuo *ind)
{
	int pontoMutacao;
	int mutaFlag = rand() % 2;

	if (mutaFlag) {
		pontoMutacao = rand() % 3;
		ind->cromossomo[pontoMutacao] = rand() % 12;
	}
}

void mostrarDadosIndividuo(individuo ind)
{
	printf("Valor do fitness (aptidao): %.2f\n", ind.fitness);
	printf("Cromossomo: ");
	imprimirCromossomo(ind.cromossomo);
	printf("\n\n");
}

void imprimirCromossomo(enum notas *cromossomo)
{
	int i;
	for (i = 0; i < T_CROMOSSOMO; i++) {
		switch (cromossomo[i]) {
		case 0: printf("DO "); break;
		case 1: printf("DOs "); break;
		case 2: printf("RE "); break;
		case 3: printf("REs "); break;
		case 4: printf("MI "); break;
		case 5: printf("FA "); break;
		case 6: printf("FAs "); break;
		case 7: printf("SOL "); break;
		case 8: printf("SOLs "); break;
		case 9: printf("LA "); break;
		case 10: printf("LAs "); break;
		case 11: printf("SI "); break;
		}
	}
}
