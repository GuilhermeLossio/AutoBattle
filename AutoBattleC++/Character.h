#pragma once
#include "Grid.h"
#include "Character.h"
#include "Types.h"

using namespace std;

class Character
{
public:

    Character(Types::CharacterClass charcaterClass);
    ~Character();

    
    float Health;
    float BaseDamage;
    float DamageMultiplier;
    //public GridBox currentBox;
    int PlayerIndex;
    //public Character Target{ get; set; }


    //Percebi que o utilizamento de instancia aqui estava feito incorretamente.
    shared_ptr<Character> target;
    //Character* target;

    //Escolhi fazer a inicialização da variavel para que a mesma não tenha possibilidade de conter um valor nulo e o jogador comecar morto.
    bool IsDead = false;
    char Icon;

    Types::GridBox currentBox;

    bool TakeDamage(float amount);


    //????
    //int getIndex(std::vector<Types::GridBox*> v, int index);

    void Die();

    void WalkTo(bool CanWalk);

    void StartTurn(Grid* battlefield);

    bool CheckCloseTargets(Grid* battlefield);

    void Attack(Character* target);


};

