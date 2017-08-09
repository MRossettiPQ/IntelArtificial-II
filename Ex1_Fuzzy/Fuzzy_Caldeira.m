[System]
Name='FUZZY_CALDEIRA'
Type='mamdani'
Version=2.0
NumInputs=2
NumOutputs=2
NumRules=10
AndMethod='min'
OrMethod='max'
ImpMethod='min'
AggMethod='max'
DefuzzMethod='centroid'

[Input1]
Name='Temperatura'
Range=[0 1000]
NumMFs=5
MF1='Extrema':'trimf',[850 950 1000]
MF2='Quente':'trimf',[600 750 900]
MF3='Normal':'trimf',[450 550 650]
MF4='Baixa':'trimf',[45 275 500]
MF5='Desligada':'trimf',[0 25 50]

[Input2]
Name='Tempo'
Range=[0 23]
NumMFs=3
MF1='Horario_de_Trabalho':'trimf',[0 4 8]
MF2='Pos_Horario':'trimf',[8 12 16]
MF3='Pre_Horario':'trimf',[16 20 23]

[Output1]
Name='AberturaAgua'
Range=[0 100]
NumMFs=5
MF1='CompAberto':'trimf',[90 95 100]
MF2='QuaseTodoAberto':'trimf',[75 85 90]
MF3='MeioAberto':'trimf',[50 60 75]
MF4='QuaseAberto':'trimf',[0 25 50]
MF5='Fechado':'trimf',[0 0 0]

[Output2]
Name='AberturaGas'
Range=[0 100]
NumMFs=5
MF1='CompAberto':'trimf',[90 95 100]
MF2='QuaseTodoAberto':'trimf',[75 85 90]
MF3='MeioAberto':'trimf',[50 60 75]
MF4='QuaseAberto':'trimf',[0 25 50]
MF5='Fechado':'trimf',[0 0 0]

[Rules]
5 1, 5 1 (1) : 1
5 2, 4 2 (1) : 1
5 3, 4 3 (1) : 1
4 1, 4 3 (1) : 1
4 2, 3 3 (1) : 1
4 3, 4 3 (1) : 1
3 1, 4 4 (1) : 1
3 2, 2 4 (1) : 1
3 3, 4 4 (1) : 1
2 1, 2 3 (1) : 1
2 2, 1 4 (1) : 1
2 3, 2 3 (1) : 1
1 1, 1 5 (1) : 1
1 2, 1 5 (1) : 1
1 3, 1 5 (1) : 1