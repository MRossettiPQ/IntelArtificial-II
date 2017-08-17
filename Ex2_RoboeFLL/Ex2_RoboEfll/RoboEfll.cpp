#include <iostream>
#include "FuzzyRule.h"
#include "FuzzyComposition.h"
#include "Fuzzy.h"
#include "FuzzyRuleConsequent.h"
#include "FuzzyOutput.h"
#include "FuzzyInput.h"
#include "FuzzyIO.h"
#include "FuzzySet.h"
#include "FuzzyRuleAntecedent.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(int argc, char *argv[]) 
{
    Fuzzy* fuzzy = new Fuzzy();
    // FuzzyInput
		//Variaveis Linguisticas Direita
		FuzzyInput* distanciaD = new FuzzyInput(1);																							//CRIAÇÃO ENTRADAS DIREITA
		FuzzySet* PertoD	   = new FuzzySet(0, 20, 20, 40);																				//DEFINIÇÃO DE VARIAVEL LINGUISTICA PARA DISTANCIA PERTO DO MOTOR DIREITA
			distanciaD->addFuzzySet(PertoD);																								//ADIÇÃO VARIAVEL DIREITA PERTO
		FuzzySet* SeguroD      = new FuzzySet(30, 50, 50, 70);																				//DEFINIÇÃO DE VARIAVEL LINGUISTICA PARA DISTANCIA SEGURO DO MOTOR DIREITA
			distanciaD->addFuzzySet(SeguroD);																								//ADIÇÃO VARIAVEL DIREITA SEGURO
		FuzzySet* LongeD       = new FuzzySet(60, 80, 80, 120);																				//DEFINIÇÃO DE VARIAVEL LINGUISTICA PARA DISTANCIA LONGE DO MOTOR DIREITA
			distanciaD->addFuzzySet(LongeD);																								//ADIÇÃO VARIAVEL DIREITA LONGE
		fuzzy->addFuzzyInput(distanciaD);																									//ADIÇÃO ENTRADAS DIREITA
	
		//Variaveis Linguisticas Esquerda
		FuzzyInput* distanciaE = new FuzzyInput(2);																							//CRIAÇÃO ENTRADAS ESQUERDA
		FuzzySet* PertoE       = new FuzzySet(0, 20, 20, 40);																				//DEFINIÇÃO DE VARIAVEL LINGUISTICA PARA DISTANCIA PERTO DO MOTOR ESQUERDA
			distanciaE->addFuzzySet(PertoE);																								//ADIÇÃO VARIAVEL ESQUERDA PERTO
		FuzzySet* SeguroE      = new FuzzySet(30, 50, 50, 70);																				//DEFINIÇÃO DE VARIAVEL LINGUISTICA PARA DISTANCIA SEGURO DO MOTOR ESQUERDA
			distanciaE->addFuzzySet(SeguroE);																								//ADIÇÃO VARIAVEL ESQUERDA SEGURO
		FuzzySet* LongeE       = new FuzzySet(60, 80, 80, 120);																				//DEFINIÇÃO DE VARIAVEL LINGUISTICA PARA DISTANCIA LONGE DO MOTOR ESQUERDA
			distanciaE->addFuzzySet(LongeE);																								//ADIÇÃO VARIAVEL ESQUERDA LONGE
		fuzzy->addFuzzyInput(distanciaE);																									//ADIÇÃO ENTRADAS ESQUERDA

    // FuzzyOutput
		//Variaveis Linguisticas Direita
		FuzzyOutput* motorD  = new FuzzyOutput(1);																							//CRIAÇÃO SAIDAS DIREITA
		FuzzySet* InvertidoD = new FuzzySet(-70, -120, -120, -150);																			//DEFINIÇÃO DE VARIAVEL LINGUISTICA PARA VELOCIDADE INVERTIDA DO MOTOR DIREITA
			motorD->addFuzzySet(InvertidoD);																								//ADIÇÃO VARIAVEL INVERTIDA DIREITA
		FuzzySet* BaixaD     = new FuzzySet(0, 40, 40, 80);																					//DEFINIÇÃO DE VARIAVEL LINGUISTICA PARA VELOCIDADE BAIXA DO MOTOR DIREITA
			motorD->addFuzzySet(BaixaD);																									//ADIÇÃO VARIAVEL BAIXA DIREITA
		FuzzySet* MediaD     = new FuzzySet(70, 120, 120, 150);																				//DEFINIÇÃO DE VARIAVEL LINGUISTICA PARA VELOCIDADE MEDIA DO MOTOR DIREITA
			motorD->addFuzzySet(MediaD);																									//ADIÇÃO VARIAVEL MEDIA DIREITA
		FuzzySet* MaximaD    = new FuzzySet(140, 200, 200, 255);																			//DEFINIÇÃO DE VARIAVEL LINGUISTICA PARA VELOCIDADE MAXIMA DO MOTOR DIREITA
			motorD->addFuzzySet(MaximaD);																									//ADIÇÃO VARIAVEL MAXIMA DIREITA
		fuzzy->addFuzzyOutput(motorD);																										//ADIÇÃO SAIDAS DIREITA

		//Variaveis Linguisticas Esquerda
		FuzzyOutput* motorE  = new FuzzyOutput(2);																							//CRIAÇÃO SAIDAS ESQUERDA
		FuzzySet* InvertidoE = new FuzzySet(-70, -120, -120, -150);																			//DEFINIÇÃO DE VARIAVEL LINGUISTICA PARA VELOCIDADE INVERTIDA DO MOTOR ESQUERDO
			motorE->addFuzzySet(InvertidoE);																								//ADIÇÃO VARIAVEL INVERTIDA ESQUERDA
		FuzzySet* BaixaE     = new FuzzySet(0, 40, 40, 80);																					//DEFINIÇÃO DE VARIAVEL LINGUISTICA PARA VELOCIDADE BAIXA DO MOTOR ESQUERDO
			motorE->addFuzzySet(BaixaE);																									//ADIÇÃO VARIAVEL BAIXA ESQUERDA
		FuzzySet* MediaE     = new FuzzySet(70, 120, 120, 150);																				//DEFINIÇÃO DE VARIAVEL LINGUISTICA PARA VELOCIDADE MEDIA DO MOTOR ESQUERDO
			motorE->addFuzzySet(MediaE);																									//ADIÇÃO VARIAVEL MEDIA ESQUERDA
		FuzzySet* MaximaE    = new FuzzySet(140, 200, 200, 255);																			//DEFINIÇÃO DE VARIAVEL LINGUISTICA PARA VELOCIDADE MAXIMA DO MOTOR ESQUERDO
			motorE->addFuzzySet(MaximaE);																									//ADIÇÃO VARIAVEL MAXIMA ESQUERDA
		fuzzy->addFuzzyOutput(motorE);																										//ADIÇÃO SAIDAS ESQUERDA
	
	// CONSTRUÇÃO DAS REGRAS DE INFERENCIA
		//Regra 1
		FuzzyRuleAntecedent* distanciaPerto      = new FuzzyRuleAntecedent();																//Cria Antecedente
			distanciaPerto->joinWithAND(PertoD, PertoE);																					//Associação sensor Esquerdo com o Direito
 		FuzzyRuleConsequent* velocidadeInvertida = new FuzzyRuleConsequent();																//Cria Consequencia
			velocidadeInvertida->addOutput(InvertidoD);																						//Define a Saida Direita
			velocidadeInvertida->addOutput(InvertidoE);																						//Define a Saida Esquerda
		FuzzyRule* Regra1 = new FuzzyRule(1, distanciaPerto, velocidadeInvertida);															//SE sensor Direito resulta "PERTO" e sensor Esquerdo resulta "PERTO", ENTÃO ele INVERTERA a rotação do motor
			fuzzy->addFuzzyRule(Regra1);																									//Adiciona a regra 1

		//Regra 2
		FuzzyRuleAntecedent* distanciaPertoEsquerda1 = new FuzzyRuleAntecedent();															//Cria Antecedente
			distanciaPertoEsquerda1->joinWithAND(SeguroD, PertoE);																			//Associação sensor Esquerdo com o Direito
		FuzzyRuleConsequent* virarDireita1			 = new FuzzyRuleConsequent();															//Cria Consequencia
			velocidadeInvertida->addOutput(InvertidoD);																						//Define a Saida Direita
			velocidadeInvertida->addOutput(MediaE);																							//Define a Saida Esquerda
		FuzzyRule* Regra2 = new FuzzyRule(12, distanciaPertoEsquerda1, virarDireita1);														//SE sensor Direito resulta "SEGURO" e sensor Esquerdo resulta "PERTO", ENTÃO ele irar virar a DIREITA
			fuzzy->addFuzzyRule(Regra2);																									//Adiciona a regra 2

		//Regra 3	
		FuzzyRuleAntecedent* distanciaPertoEsquerda2 = new FuzzyRuleAntecedent();															//Cria Antecedente
			distanciaPertoEsquerda2->joinWithAND(LongeD, PertoE);																			//Associação sensor Esquerdo com o Direito
		FuzzyRuleConsequent* virarDireita2			 = new FuzzyRuleConsequent();															//Cria Consequencia
			velocidadeInvertida->addOutput(BaixaD);																							//Define a Saida Direita
			velocidadeInvertida->addOutput(MediaE);																							//Define a Saida Esquerda
		FuzzyRule* Regra3 = new FuzzyRule(3, distanciaPertoEsquerda2, virarDireita2);														//SE sensor Direito resulta "LONGE" e sensor Esquerdo resulta "PERTO", ENTÃO ele irar virar a DIREITA
			fuzzy->addFuzzyRule(Regra3);																									//Adiciona a regra 3

		//Regra 4
		FuzzyRuleAntecedent* distanciaPertoDireita1 = new FuzzyRuleAntecedent();															//Cria Antecedente
			distanciaPertoDireita1->joinWithAND(PertoD, SeguroE);																			//Associação sensor Esquerdo com o Direito
		FuzzyRuleConsequent* virarEsquerda1			= new FuzzyRuleConsequent();															//Cria Consequencia
			velocidadeInvertida->addOutput(MediaD);																							//Define a Saida Direita
			velocidadeInvertida->addOutput(InvertidoE);																						//Define a Saida Esquerda
		FuzzyRule* Regra4 = new FuzzyRule(4, distanciaPertoDireita1, virarEsquerda1);														//SE sensor Direito resulta "PERTO" e sensor Esquerdo resulta "SEGURO", ENTÃO ele irar virar a ESQUERDA
			fuzzy->addFuzzyRule(Regra4);																									//Adiciona a regra 4

		//Regra 5
		FuzzyRuleAntecedent* distanciaPertoDireita2 = new FuzzyRuleAntecedent();															//Cria Antecedente
			distanciaPertoDireita2->joinWithAND(PertoD, LongeE);																			//Associação sensor Esquerdo com o Direito
		FuzzyRuleConsequent* virarEsquerda2			= new FuzzyRuleConsequent();															//Cria Consequencia
			velocidadeInvertida->addOutput(MediaD);																							//Define a Saida Direita
			velocidadeInvertida->addOutput(BaixaE);																							//Define a Saida Esquerda
		FuzzyRule* Regra5 = new FuzzyRule(5, distanciaPertoDireita2, virarEsquerda2);														//SE sensor Direito resulta "PERTO" e sensor Esquerdo resulta "LONGE", ENTÃO ele irar virar a ESQUERDA
			fuzzy->addFuzzyRule(Regra5);																									//Adiciona a regra 5
		
		//Regra 6
		FuzzyRuleAntecedent* distanciaSeguroEsquerda1 = new FuzzyRuleAntecedent();															//Cria Antecedente
			distanciaSeguroEsquerda1->joinWithAND(SeguroD, SeguroE);																		//Associação sensor Esquerdo com o Direito
		FuzzyRuleConsequent* emFrente1				  = new FuzzyRuleConsequent();															//Cria Consequencia
			velocidadeInvertida->addOutput(MediaD);																							//Define a Saida Direita
			velocidadeInvertida->addOutput(MediaE);																							//Define a Saida Esquerda
		FuzzyRule* Regra6 = new FuzzyRule(6, distanciaSeguroEsquerda1, emFrente1);															//SE sensor Direito resulta "SEGURO" e sensor Esquerdo resulta "SEGURO", ENTÃO ele ira seguir em FRENTE
			fuzzy->addFuzzyRule(Regra6);																									//Adiciona a regra 6

		//Regra 7
		FuzzyRuleAntecedent* distanciaSeguroEsquerda2 = new FuzzyRuleAntecedent();															//Cria Antecedente
			distanciaSeguroEsquerda2->joinWithAND(LongeD, SeguroE);																			//Associação sensor Esquerdo com o Direito
		FuzzyRuleConsequent* emFrente2				  = new FuzzyRuleConsequent();															//Cria Consequencia
			velocidadeInvertida->addOutput(MediaD);																							//Define a Saida Direita
			velocidadeInvertida->addOutput(MediaE);																							//Define a Saida Esquerda
		FuzzyRule* Regra7 = new FuzzyRule(7, distanciaSeguroEsquerda1, emFrente2);															//SE sensor Direito resulta "LONGE" e sensor Esquerdo resulta "SEGURO", ENTÃO ele ira seguir em FRENTE
			fuzzy->addFuzzyRule(Regra7);																									//Adiciona a regra 7

		//Regra 8
		FuzzyRuleAntecedent* distanciaSeguroDireita = new FuzzyRuleAntecedent();															//Cria Antecedente
			distanciaSeguroDireita->joinWithAND(SeguroD, LongeE);																			//Associação sensor Esquerdo com o Direito
		FuzzyRuleConsequent* emFrente3				= new FuzzyRuleConsequent();															//Cria Consequencia
			velocidadeInvertida->addOutput(MediaD);																							//Define a Saida Direita
			velocidadeInvertida->addOutput(MediaE);																							//Define a Saida Esquerda
		FuzzyRule* Regra8 = new FuzzyRule(8, distanciaSeguroDireita, emFrente3);															//SE sensor Direito resulta "SEGURO" e sensor Esquerdo resulta "LONGE", ENTÃO ele ira seguir em FRENTE
			fuzzy->addFuzzyRule(Regra8);																									//Adiciona a regra 8

		//Regra 9
		FuzzyRuleAntecedent* distanciaLonge			= new FuzzyRuleAntecedent();															//Cria Antecedente
			distanciaLonge->joinWithAND(LongeD, LongeE);																					//Associação sensor Esquerdo com o Direito
		FuzzyRuleConsequent* emFrente4				= new FuzzyRuleConsequent();															//Cria Consequencia
			velocidadeInvertida->addOutput(MaximaD);																						//Define a Saida Direita
			velocidadeInvertida->addOutput(MaximaE);																						//Define a Saida Esquerda
		FuzzyRule* Regra9 = new FuzzyRule(9, distanciaLonge, emFrente4);																	//SE sensor Direito resulta "LONGE" e sensor Esquerdo resulta "LONGE", ENTÃO ele ira seguir em FRENTE
			fuzzy->addFuzzyRule(Regra9);																									//Adiciona a regra 9


	int cont, randomico1, randomico2;																										//VARIAVEIS SIMULAÇÃO
	for (cont = 0; cont <= 20; cont++)
	{
		srand(time(NULL));																													

		randomico1 = rand() % 120;																											//CHAMADA E CRIAÇÃO DE VALOR RANDOMICO PARA ENTRADA DO SENSOR
		randomico2 = rand() % 120;																											//CHAMADA E CRIAÇÃO DE VALOR RANDOMICO PARA ENTRADA DO SENSOR
		cout << "VALOR SENSOR 1: " << randomico1 << ", VALOR SENSOR 2: " << randomico2 << endl;												//IMPRESSÃO DOS VALORES LIDOS PELO SENSOR

		fuzzy->setInput(1, randomico1);																										//CHAMADA DA FUNÇÃO QUE FUZZIFICA OS VALORES DO SENSOR 1
		fuzzy->setInput(2, randomico2);																										//CHAMADA DA FUNÇÃO QUE FUZZIFICA OS VALORES DO SENSOR 2

		fuzzy->fuzzify();																													//PROCESSAMENTO DAS REGRAS DE INFERENCIA

		cout << "Regra1: " << Regra1->isFired() << ", Regra2: " << Regra2->isFired() << ", Regra3: " << Regra3->isFired() << endl;			//IMPRESSÃO DA REGRA QUE FOI ATIVADA
		cout << "Regra4: " << Regra4->isFired() << ", Regra5: " << Regra5->isFired() << ", Regra6: " << Regra6->isFired() << endl;			//IMPRESSÃO DA REGRA QUE FOI ATIVADA
		cout << "Regra7: " << Regra7->isFired() << ", Regra8: " << Regra8->isFired() << ", Regra9: " << Regra9->isFired() << endl;			//IMPRESSÃO DA REGRA QUE FOI ATIVADA


		float output1 = fuzzy->defuzzify(1);																								//RECEPÇÃO DO VALOR APLICADO NO MOTOR DIREITO
		float output2 = fuzzy->defuzzify(2);																								//RECEPÇÃO DO VALOR APLICADO NO MOTOR ESQUERDO

		cout << "Motor Direita: " << output1 << ", Motor Esquerda: " << output2 << endl;													//IMPRESSÃO DA VELOCIDADE DOS MOTORES APLICADA
		cout << "\n" << endl;
	}
	system("pause");
    return 0;
}
