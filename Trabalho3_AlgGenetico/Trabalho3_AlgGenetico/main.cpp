#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_CROMOSSOMO  6
#define MAX_GERACOES    100
#define MAX_POP_SIZE    20

#define TX_MUTACAO 0.3
#define MAX_INSTRUCAO 6

float base[][2] = {
	{ 0 , 6 },
	{ 7 , 10 },
	{ 10, 0 },
	{ 15, 9 },
	{ 16, 5 },
	{ 20, 7 }
};

typedef enum {
	ERMO = 1, TURVO, TORRES, PALMAS, BRASILIA, BOSTON
} instrucao;

typedef instrucao cromossomo[MAX_CROMOSSOMO];

typedef struct {
	cromossomo g_cromo;
	float fitness;
} individuo_t;

typedef struct {
	individuo_t individuos[MAX_POP_SIZE];
	unsigned int geracao;
	float media_fitness_pop;
} pop_t;

/*
Cabeçalho das rotinas auxiliares
*/
individuo_t geraIndividuo();
void iniciaPopulacao(pop_t *populacao);
void calculaFitness(individuo_t *ind);
int genesDistintos(cromossomo numeros);
void ordenaPopulacao(pop_t *populacao);
individuo_t* reproducao(pop_t populacao);
individuo_t torneio(pop_t populacao);
individuo_t cruzamento(individuo_t pai, individuo_t mae);
void mutacao(individuo_t filhos[]);
void selecaoNatural(pop_t *populacao, individuo_t filhos[]);
int quemEuSou(individuo_t ind);
void mostraIndividuo(individuo_t umIndividuo);
float pRandom();

/*
Função principal
*/
int main()
{
	srand(time(NULL));
	int i, geracao = 0;
	float soma = 0;

	pop_t populacao;
	iniciaPopulacao(&populacao);


	printf("Geracao Aptidao           Solucao\n");
	while (populacao.geracao < MAX_GERACOES)
	{
		//printf("Avaliando...\n");
		// Aqui icorre a avaliação da aptidão de cada indivíduo
		for (i = 0, soma = 0; i < MAX_POP_SIZE; i++)
		{
			calculaFitness(&populacao.individuos[i]);
			soma += populacao.individuos[i].fitness;
		}
		populacao.media_fitness_pop = soma / i;

		//mostraPopulacao(populacao);

		//printf("Evoluindo...");
		// Aqui ocorre a evolução: ordenação -> reprodução -> seleção
		ordenaPopulacao(&populacao);
		selecaoNatural(&populacao, reproducao(populacao));

		// Mostra a melhor solução em cada época
		printf("%d\t", populacao.geracao++);
		mostraIndividuo(populacao.individuos[0]);
	}

	return 0;
}

/*
* Constrói um novo indivíduo
*/
individuo_t geraIndividuo()
{
	individuo_t new_ind;
	int i, tamanho_ind = 6;//rand() % (MAX_CROMOSSOMO - 2) + 3;

	for (i = 0; i < tamanho_ind; i++)
		new_ind.g_cromo[i] = (instrucao)(rand() % MAX_INSTRUCAO + 1);
	/*
	for (i = tamanho_ind; i < MAX_CROMOSSOMO; i++)
	new_ind.g_cromo[i] = VAZIO;
	*/
	new_ind.fitness = 0.0;

	return new_ind;
}

/*
* Constrói uma nova população
*/
void iniciaPopulacao(pop_t *populacao)
{
	int i;

	for (i = 0; i < MAX_POP_SIZE; i++)
		populacao->individuos[i] = geraIndividuo();

	populacao->geracao = 0;
	populacao->media_fitness_pop = 0.0;
}
/*
* Função fitness - Calcula a aptidão do indivíduo
* Precisa ser aprimorada
*/
void calculaFitness(individuo_t *ind)
{
	int i;
	float caminho, xQuad, yQuad;

	for (i = 1, caminho = 0; i < quemEuSou(*ind); i++)
	{
		xQuad = pow(base[ind->g_cromo[i - 1] - 1][0] - base[ind->g_cromo[i] - 1][0], 2);
		yQuad = pow(base[ind->g_cromo[i - 1] - 1][1] - base[ind->g_cromo[i] - 1][1], 2);
		caminho += sqrt(xQuad + yQuad);
		//printf("%c - %c: %f\n",(ind->g_cromo[i-1]+64), (ind->g_cromo[i]+64), sqrt(xQuad+yQuad));
	}

	xQuad = pow(base[ind->g_cromo[i - 1] - 1][0] - base[ind->g_cromo[0] - 1][0], 2);
	yQuad = pow(base[ind->g_cromo[i - 1] - 1][1] - base[ind->g_cromo[0] - 1][1], 2);
	caminho += sqrt(xQuad + yQuad);
	//printf("%c - %c: %f\n",(ind->g_cromo[i-1]+64), (ind->g_cromo[0]+64), sqrt(xQuad+yQuad));
	//printf("Caminho: %f\n", caminho);
	//ind->fitness = caminho*(MAX_CROMOSSOMO-genesDistintos(ind->g_cromo)+1);
	ind->fitness = pow(caminho, (MAX_CROMOSSOMO - genesDistintos(ind->g_cromo) + 1));
}

/*
* Retorna quantos valores distintos estão presentes no cromossomo
*/
int genesDistintos(cromossomo numeros)
{
	int i, j, n = 1;
	for (i = 1; i < MAX_CROMOSSOMO; i++)
	{
		n++;
		for (j = 0; j < i; j++)
			if (numeros[j] == numeros[i])
			{
				n--;
				break;
			}
	}
	return n;
}

void ordenaPopulacao(pop_t *populacao)
{
	int i, j;
	individuo_t aux;

	for (i = 0; i < MAX_POP_SIZE; i++) {
		for (j = 0; j < MAX_POP_SIZE - 1; j++) {
			if (populacao->individuos[j].fitness > populacao->individuos[j + 1].fitness) {
				aux = populacao->individuos[j];
				populacao->individuos[j] = populacao->individuos[j + 1];
				populacao->individuos[j + 1] = aux;
			}
		}
	}
}

/*
* Retorna um vetor de filhos para compor uma nova geração
*/
individuo_t* reproducao(pop_t populacao)
{
	int i;
	individuo_t* filhos = (individuo_t*)malloc(sizeof(individuo_t)*MAX_POP_SIZE / 2);

	for (i = 0; i < MAX_POP_SIZE / 2; i++)
		filhos[i] = cruzamento(torneio(populacao), torneio(populacao));

	mutacao(filhos);

	return filhos;
}

/*
* Retorna um pai vencedor entre a população
*/
individuo_t torneio(pop_t populacao)
{   // O número gerado entre colchetes é um índice, sendo que os índices menores são mais prováveis
	return populacao.individuos[(int)lround(pRandom()*(MAX_POP_SIZE - 1))];
}

/*
* Cruza dois individuos selecionados e retorna seu filho - crossing over
*/
individuo_t cruzamento(individuo_t pai, individuo_t mae)
{
	individuo_t filho;
	int i, cut = rand() % (quemEuSou(filho)); //Esta linha determina com quanto cada parte contribuirá

	if (rand() % 10 < 5) { // Esta linha determina quem dará a primeira parte do cromossomo
		for (i = 0; i < cut; i++)
			filho.g_cromo[i] = pai.g_cromo[i];

		for (i = cut; i < quemEuSou(filho); i++)
			filho.g_cromo[i] = mae.g_cromo[i];
	}
	else {
		for (i = 0; i < cut; i++)
			filho.g_cromo[i] = mae.g_cromo[i];


		for (i = cut; i < quemEuSou(filho); i++)
			filho.g_cromo[i] = pai.g_cromo[i];
	}

	return filho;
}

/*
* Percorre os cromossomos de cada filho, criando mutações em alguns genes
*/
void mutacao(individuo_t filhos[])
{
	int i, j;
	for (i = 0; i < MAX_POP_SIZE / 2; i++)
		for (j = 0; j < quemEuSou(filhos[i]); j++)
			if (pRandom() < TX_MUTACAO * 2) // Determina a probabilidade de que a mutação ocorra
				filhos[i].g_cromo[j] = (instrucao)(rand() % MAX_INSTRUCAO + 1);
}

/*
* Seleção por truncamento, talvez não muito eficiente
* Trocar por seleção por roleta ou torneio pode ser uma boa opção
*/
void selecaoNatural(pop_t *populacao, individuo_t filhos[])
{
	int i;
	for (i = 0; i < MAX_POP_SIZE / 2; i++)
		populacao->individuos[MAX_POP_SIZE - i - 1] = filhos[i];
	free(filhos);
}

/*
* Retorna o tamanho do cromossomo do individuo
*/
int quemEuSou(individuo_t ind)
{
	int i = 0;
	while (i < MAX_CROMOSSOMO) i++;

	return i;
}

/*
* Exibe a população no console
*/
/*void mostraPopulacao(pop_t populacao)
{
int i, j;

printf("Geracao:                %d\n", populacao.geracao);
printf("Media fitness           %.2f\n", populacao.media_fitness_pop);

for (i = 0; i < MAX_POP_SIZE; i++)
{
printf("%d. ", i);

mostraIndividuo(populacao.individuos[i]);

printf("\n\n");
}
}

/*
* Apenas para fim de debug, usada para mostrar os filhos
*/
/*void mostraIndividuos(individuo_t individuos[])
{
int i, j;
for (i = 0; i < MAX_POP_SIZE/2; i++)
{
printf("%d. ", i);

mostraIndividuo(individuos[i]);

printf("\n\n");
}
}

/*
* Exibe os dados de um individuo
*/
void mostraIndividuo(individuo_t umIndividuo)
{
	int j;
	printf("%5.2f\t\t", umIndividuo.fitness);
	for (j = 0; j < MAX_CROMOSSOMO; j++)
		printf("%d ", umIndividuo.g_cromo[j]);
	printf("\n");
}

/*
* Retorna um valor aleatório entre 0 e 1, gerado sob probabilidade
*/
float pRandom()
{
	float x;
	float y;

	do {
		x = (rand() % 10) / 10.0; // Número
		y = (rand() % 10) / 10.0; // Nota
	} while (y > exp(-3 * x));   // Derivada

	return x;
}
