#include "Grid.h"
#include "BattleField.h"
#include "Types.h"
#include "Character.h"
#include <iostream>
#include "BattleField.h"
#include <list>
#include <string>
#include <vector>

using namespace std;


BattleField::BattleField() {
    grid = new Grid(5, 5);
    AllPlayers = new list<Character>();
    int currentTurn = 0;
}

void BattleField::Setup()
{
    GetPlayerChoice();
    StartGame();
}

void BattleField::GetPlayerChoice()
{
    string choice;
    while (true) {
        //asks for the player to choose between for possible classes via console.
        printf("Choose Between One of this Classes:\n");
        printf("[1] Paladin, [2] Warrior, [3] Cleric, [4] Archer\n");
        //store the player choice in a variable

        getline(cin, choice);
        if (choice.length() == 1)
        {
            if (choice[0] == '1'
                || choice[0] == '2'
                || choice[0] == '3'
                || choice[0] == '4')
            {
                break;
            }
        }
    }

    //I removed the switch case for being really desnecessary.
    CreatePlayerCharacter(stoi(choice));
}

void BattleField::CreatePlayerCharacter(int classIndex)
{

    Types::CharacterClass characterClass = static_cast<Types::CharacterClass>(classIndex);
    //Here i puted a way to show to player the character he chosed
    switch ((classIndex))
    {
    case 1:
        printf("Player Class Choice: Paladin\n");
        break;
    case 2:
        printf("Player Class Choice: Warrior\n");
        break;
    case 3:
        printf("Player Class Choice: Cleric\n");
        break;
    case 4:
        printf("Player Class Choice: Archer\n");
        break;
    }
    
    PlayerCharacter = make_shared<Character>(characterClass);
    
    PlayerCharacter->Health = 100;
    PlayerCharacter->BaseDamage = 30;
    PlayerCharacter->DamageMultiplier = 1;
    PlayerCharacter->PlayerIndex = 0;

    CreateEnemyCharacter();

}

void BattleField::CreateEnemyCharacter()
{
    //randomly choose the enemy class and set up vital variables
    int randomInteger = GetRandomInt(1, 4);

    Types::CharacterClass enemyClass = static_cast<Types::CharacterClass>(randomInteger);

    //Here i puted a switch case for the class choised.
    switch ((randomInteger))
    {
    case 1:
        printf("Enemy Class Choice: Paladin\n");
        break;
    case 2:
        printf("Enemy Class Choice: Warrior\n");
        break;
    case 3:
        printf("Enemy Class Choice: Cleric\n");
        break;
    case 4:
        printf("Enemy Class Choice: Archer\n");
        break;
    }

    EnemyCharacter = make_shared<Character>(enemyClass);

    EnemyCharacter->Health = 100;
    EnemyCharacter->BaseDamage = 30;
    EnemyCharacter->DamageMultiplier = 1;
    EnemyCharacter->PlayerIndex = 1;

}

void BattleField::StartGame()
{
    //populates the character variables and targets
    EnemyCharacter->target = PlayerCharacter;
    PlayerCharacter->target = EnemyCharacter;

    //Here we going to put the player and enemy on battlefield
    AlocatePlayers();

    AllPlayers->push_back(*PlayerCharacter);
    AllPlayers->push_back(*EnemyCharacter);

    grid->drawBattlefield(5, 5);

    StartTurn();

}

void BattleField::StartTurn() {



    currentTurn++;

    list<Character>::iterator it;

    bool otherTurn = true;

    printf("\n----------------------------------------------------------------------------------------\n");
    printf("----------------------------------------------------------------------------------------\n");
    printf("Start of the Turn %d\n\n", currentTurn);
    printf("Player Health: %.0f \n", PlayerCharacter->Health);
    printf("Player Current Location: Line: %d Column: %d \n\n", PlayerCharacter->currentBox.xIndex, PlayerCharacter->currentBox.yIndex);

    printf("Enemy Health: %.0f \n", EnemyCharacter->Health);
    printf("Enemy Current Location: Line: %d Column: %d \n\n", EnemyCharacter->currentBox.xIndex, EnemyCharacter->currentBox.yIndex);


    for (it = AllPlayers->begin(); it != AllPlayers->end(); ++it) {

        it->StartTurn(grid, otherTurn);
        otherTurn = false;
    }


    printf("Player Health: %.0f \n", PlayerCharacter->Health);
    printf("Player Current Location: Line: %d Column: %d \n\n", PlayerCharacter->currentBox.xIndex, PlayerCharacter->currentBox.yIndex);

    printf("Enemy Health: %.0f \n", EnemyCharacter->Health);
    printf("Enemy  Current Location: Line: %d Column: %d \n\n", EnemyCharacter->currentBox.xIndex, EnemyCharacter->currentBox.yIndex);

    printf("\nCurrently scenery %d\n", currentTurn);
    grid->drawBattlefield(5, 5);

    printf("\nEnd of the Turn %d\n", currentTurn);
    printf("\n----------------------------------------------------------------------------------------\n");

    HandleTurn();



}

void BattleField::HandleTurn()
{
    if (PlayerCharacter->Health <= 0)
    {
        printf("\n--------------------------------Game Over----------------------------------\n");
        printf("-----------------------------The Enemy Wins!------------------------------\n");
    }
    else if (EnemyCharacter->Health <= 0)
    {
        printf("\n--------------------------------Game Over----------------------------------\n");
        printf("-----------------------------The Player Wins!------------------------------\n");
    }
    else
    {
        printf("\n");
        printf("---------------------------Press Enter to start the next turn---------------------------");
        printf("\n");

        string PlayerInput;
        getline(cin, PlayerInput);

        StartTurn();
    }
}

int BattleField::GetRandomInt(int min, int max)
{
    
    return rand() % max + min;
}

void BattleField::AlocatePlayers()
{
    AlocatePlayerCharacter();
    AlocateEnemyCharacter();
}

void BattleField::AlocatePlayerCharacter()
{
    int random = GetRandomInt(0, ((grid->xLenght * grid->yLength) - 1));

    auto l_front = grid->grids.begin();
    advance(l_front, random);
    Types::GridBox* RandomLocation = &*l_front;

    if (!RandomLocation->ocupied)
    {
        PlayerCurrentLocation = &*l_front;
        l_front->ocupied = true;
        PlayerCharacter->currentBox = *l_front;
        printf("Player Current Location: Line: %d Column: %d \n", PlayerCharacter->currentBox.xIndex, PlayerCharacter->currentBox.yIndex);
        grid->PlayerCurrentLocation = PlayerCurrentLocation;
    }
    else
    {
        AlocatePlayerCharacter();
    }
}

void BattleField::AlocateEnemyCharacter()
{
    
    int random = GetRandomInt(0, ((grid->xLenght * grid->yLength) - 1));


    auto l_front = grid->grids.begin();
    advance(l_front, random);
    Types::GridBox* RandomLocation = &*l_front;

    if (!RandomLocation->ocupied)
    {
        EnemyCurrentLocation = &*l_front;
        l_front->ocupied = true;
        EnemyCharacter->currentBox = *l_front;
        printf("Enemy Current Location: Line: %d Column: %d \n", EnemyCharacter->currentBox.xIndex, EnemyCharacter->currentBox.yIndex);
        grid->EnemyCurrentLocation = EnemyCurrentLocation;
    }
    else
    {
        AlocateEnemyCharacter();
    }


}