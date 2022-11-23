// AutoBattleC++.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//
#include "BattleField.h"
#include <iostream>
#include <time.h>

int main()
{
    // this will transform all unitialized ints into a random value.
    srand((unsigned int)time(NULL));

    BattleField* battleField = new(BattleField);
    battleField->Setup();

}



