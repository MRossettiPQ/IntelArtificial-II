/*
	Rede Neural Multilayer - Problema do XOR
*/
#include <stdio.h>
#include <stdlib.h>

#define ENTRADAS    2
#define SAIDAS      1
#define BIAS        1
#define NR_AMOSTRAS 4
#define NR_NEURO_OC 

int dados_treinamento[NR_sAMOSTRAS][ENTRADAS + SAIDAS] = {{0, 0, 0},
                                                        {0, 1, 1}, 
                                                        {1, 0, 1},
                                                        {1, 1, 0}};

                                         
                                                        
float w_entrada_oculta[ENTRADAS + BIAS][NR_NEURO_OC];
float w_oculta_saida[NR_NEURO_OC + 1][SAIDAS];


float erro(float desejado, float obtido);
float sigmoid(float sinal);
void inicializa_pesos_sinapticos();
void mostra_pesos_sinapticos();

int main()
{

	return 0;		
}
float erro(float desejado, float obtido)
{
    return desejado - obtido;
}

float sigmoid(float sinal)
{
    return 1/(1 - exp(sinal));
}

void inicializa_pesos_sinapticos()
{
    int i, j;
    for(i = 0; i <  ENTRADAS+BIAS; i++)
    {
        for(j = 0; j < NR_NEURO_OC; j++)
        {
            w_entrada_oculta[i][j] = 0.0;
        }
    }
    
    for(i = 0; i <  NR_NEURO_OC+BIAS; i++)
    {
        for(j = 0; j < SAIDAS; j++)
        {
            w_oculta_saida[i][j] = 0.0;
        }
    }
}
void mostra_pesos_sinapticos()
{

}