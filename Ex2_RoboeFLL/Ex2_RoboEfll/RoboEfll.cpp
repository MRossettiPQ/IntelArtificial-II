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

int main(int argc, char *argv[]) {
    Fuzzy* fuzzy = new Fuzzy();

    // FuzzyInput
    FuzzyInput* distanciaD = new FuzzyInput(1);
    FuzzySet* PertoD = new FuzzySet(0, 20, 20, 40);
		distanciaD->addFuzzySet(PertoD);
    FuzzySet* SeguroD = new FuzzySet(30, 50, 50, 70);
		distanciaD->addFuzzySet(SeguroD);
    FuzzySet* LongeD = new FuzzySet(60, 80, 80, 120);
		distanciaD->addFuzzySet(LongeD);
    fuzzy->addFuzzyInput(distanciaD);

	FuzzyInput* distanciaE = new FuzzyInput(2);
	FuzzySet* PertoE = new FuzzySet(0, 20, 20, 40);
		distanciaE->addFuzzySet(PertoE);
	FuzzySet* SeguroE = new FuzzySet(30, 50, 50, 70);
		distanciaE->addFuzzySet(SeguroE);
	FuzzySet* LongeE = new FuzzySet(60, 80, 80, 120);
		distanciaE->addFuzzySet(LongeE);
	fuzzy->addFuzzyInput(distanciaE);

    // FuzzyOutput
    FuzzyOutput* motorD = new FuzzyOutput(1);
	FuzzySet* InvertidoD = new FuzzySet(-70, -120, -120, -150);
		motorD->addFuzzySet(InvertidoD);
    FuzzySet* BaixaD = new FuzzySet(0, 40, 40, 80);
		motorD->addFuzzySet(BaixaD);
    FuzzySet* MediaD = new FuzzySet(70, 120, 120, 150);
		motorD->addFuzzySet(MediaD);
    FuzzySet* MaximaD = new FuzzySet(140, 200, 200, 255);
		motorD->addFuzzySet(MaximaD);
    fuzzy->addFuzzyOutput(motorD);

	FuzzyOutput* motorE = new FuzzyOutput(2);
	FuzzySet* InvertidoE = new FuzzySet(-70, -120, -120, -150);
		motorE->addFuzzySet(InvertidoE);
	FuzzySet* BaixaE = new FuzzySet(0, 40, 40, 80);
		motorE->addFuzzySet(BaixaE);
	FuzzySet* MediaE = new FuzzySet(70, 120, 120, 150);
		motorE->addFuzzySet(MediaE);
	FuzzySet* MaximaE = new FuzzySet(140, 200, 200, 255);
		motorE->addFuzzySet(MaximaE);
	fuzzy->addFuzzyOutput(motorE);
	
	// Building FuzzyRule
		//Regra 1
    FuzzyRuleAntecedent* distanciaPerto      = new FuzzyRuleAntecedent();
		distanciaPerto->joinWithAND(PertoD, PertoE);
    FuzzyRuleConsequent* velocidadeInvertida = new FuzzyRuleConsequent();
		velocidadeInvertida->addOutput(InvertidoD);
		velocidadeInvertida->addOutput(InvertidoE);

    FuzzyRule* Regra1 = new FuzzyRule(1, distanciaPerto, velocidadeInvertida);
		fuzzy->addFuzzyRule(Regra1);

		//Regra 2
	FuzzyRuleAntecedent* distanciaPertoEsquerda1 = new FuzzyRuleAntecedent();
		distanciaPerto->joinWithAND(SeguroD, PertoE);
	FuzzyRuleConsequent* virarDireita1 = new FuzzyRuleConsequent();
		velocidadeInvertida->addOutput(InvertidoD);
		velocidadeInvertida->addOutput(MediaE);

	FuzzyRule* Regra2 = new FuzzyRule(12, distanciaPertoEsquerda1, virarDireita1);
		fuzzy->addFuzzyRule(Regra2);

		//Regra 3
	FuzzyRuleAntecedent* distanciaPertoEsquerda2 = new FuzzyRuleAntecedent();
		distanciaPerto->joinWithAND(LongeD, PertoE);
	FuzzyRuleConsequent* virarDireita2 = new FuzzyRuleConsequent();
		velocidadeInvertida->addOutput(BaixaD);
		velocidadeInvertida->addOutput(MediaE);

	FuzzyRule* Regra3 = new FuzzyRule(3, distanciaPertoEsquerda2, virarDireita2);
		fuzzy->addFuzzyRule(Regra3);

		//Regra 4
	FuzzyRuleAntecedent* distanciaPertoDireita1 = new FuzzyRuleAntecedent();
		distanciaPerto->joinWithAND(PertoD, SeguroE);
	FuzzyRuleConsequent* virarEsquerda1 = new FuzzyRuleConsequent();
		velocidadeInvertida->addOutput(MediaD);
		velocidadeInvertida->addOutput(InvertidoE);

	FuzzyRule* Regra4 = new FuzzyRule(4, distanciaPertoDireita1, virarEsquerda1);
		fuzzy->addFuzzyRule(Regra4);

		//Regra 5
	FuzzyRuleAntecedent* distanciaPertoDireita2 = new FuzzyRuleAntecedent();
		distanciaPerto->joinWithAND(PertoD, LongeE);
	FuzzyRuleConsequent* virarEsquerda2 = new FuzzyRuleConsequent();
		velocidadeInvertida->addOutput(MediaD);
		velocidadeInvertida->addOutput(BaixaE);

	FuzzyRule* Regra5 = new FuzzyRule(5, distanciaPertoDireita2, virarEsquerda2);
		fuzzy->addFuzzyRule(Regra5);
		
		//Regra 6
	FuzzyRuleAntecedent* distanciaSeguroEsquerda1 = new FuzzyRuleAntecedent();
		distanciaPerto->joinWithAND(SeguroD, SeguroE);
	FuzzyRuleConsequent* emFrente1 = new FuzzyRuleConsequent();
		velocidadeInvertida->addOutput(MediaD);
		velocidadeInvertida->addOutput(MediaE);

	FuzzyRule* Regra6 = new FuzzyRule(6, distanciaSeguroEsquerda1, emFrente1);
		fuzzy->addFuzzyRule(Regra6);

		//Regra 7
	FuzzyRuleAntecedent* distanciaSeguroEsquerda2 = new FuzzyRuleAntecedent();
		distanciaPerto->joinWithAND(LongeD, SeguroE);
	FuzzyRuleConsequent* emFrente2 = new FuzzyRuleConsequent();
		velocidadeInvertida->addOutput(MediaD);
		velocidadeInvertida->addOutput(MediaE);

	FuzzyRule* Regra7 = new FuzzyRule(7, distanciaSeguroEsquerda1, emFrente2);
		fuzzy->addFuzzyRule(Regra7);

		//Regra 8
	FuzzyRuleAntecedent* distanciaSeguroDireita = new FuzzyRuleAntecedent();
		distanciaPerto->joinWithAND(SeguroD, LongeE);
	FuzzyRuleConsequent* emFrente3 = new FuzzyRuleConsequent();
		velocidadeInvertida->addOutput(MediaD);
		velocidadeInvertida->addOutput(MediaE);

	FuzzyRule* Regra8 = new FuzzyRule(8, distanciaSeguroDireita, emFrente3);
		fuzzy->addFuzzyRule(Regra8);

		//Regra 9
	FuzzyRuleAntecedent* distanciaLonge = new FuzzyRuleAntecedent();
		distanciaPerto->joinWithAND(LongeD, LongeE);
	FuzzyRuleConsequent* emFrente4 = new FuzzyRuleConsequent();
		velocidadeInvertida->addOutput(MaximaD);
		velocidadeInvertida->addOutput(MaximaE);

	FuzzyRule* Regra9 = new FuzzyRule(9, distanciaLonge, emFrente4);
		fuzzy->addFuzzyRule(Regra9);


	int cont, randomico1, randomico2;
	for (cont = 0; cont <= 10; cont++)
	{
		srand(time(NULL));
		/*
		randomico1 = rand() % 120;
		randomico2 = rand() % 120;
		*/
		fuzzy->setInput(1, 80);
		fuzzy->setInput(2, 80);

		fuzzy->fuzzify();

		cout << "Regra1: " << Regra1->isFired() << ", Regra2: " << Regra2->isFired() << ", Regra3: " << Regra3->isFired() << endl;
		cout << "Regra4: " << Regra4->isFired() << ", Regra5: " << Regra5->isFired() << ", Regra6: " << Regra6->isFired() << endl;
		cout << "Regra7: " << Regra7->isFired() << ", Regra8: " << Regra8->isFired() << ", Regra9: " << Regra9->isFired() << endl;


		float output1 = fuzzy->defuzzify(1);
		float output2 = fuzzy->defuzzify(2);

		cout << "Motor Direita: " << output1 << ", Motor Esquerda: " << output2 << endl;
		cout << "\n" << endl;
	}
	system("pause");
    return 0;
}
