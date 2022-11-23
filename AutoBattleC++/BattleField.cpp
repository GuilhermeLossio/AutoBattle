#include "Grid.h"
#include "BattleField.h"
#include "Types.h"
#include "Character.h"
#include <iostream>
#include "BattleField.h"
#include <list>
#include <string>
#include <vector>>

using namespace std;


BattleField::BattleField() {
    grid = new Grid(5, 5);
    AllPlayers = new list<Character>();
    int currentTurn = 0;

    //Testing if is necessary
    //int numberOfPossibleTiles = grid->grids.size();
    //Setup();
}

void BattleField::Setup()
{
    GetPlayerChoice();
    CreateEnemyCharacter();
    StartGame();
}

void BattleField::GetPlayerChoice()
{
    string choice;
    //asks for the player to choose between for possible classes via console.
    printf("Choose Between One of this Classes:\n");

    printf("[1] Paladin, [2] Warrior, [3] Cleric, [4] Archer");
    //store the player choice in a variable

    getline(cin, choice);

    while (true) {
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
    EnemyCharacter->BaseDamage = 20;
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

    if (currentTurn == 0)
    {
        //AllPlayers.Sort();  
    }
    list<Character>::iterator it;

    for (it = AllPlayers->begin(); it != AllPlayers->end(); ++it) {
        it->StartTurn(grid);
    }

    currentTurn++;
    HandleTurn();
}

void BattleField::HandleTurn()
{
    if (PlayerCharacter->Health == 0)
    {
        return;
    }
    else if (EnemyCharacter->Health == 0)
    {
        printf("\n");

        // endgame?

        printf("\n");

        return;
    }
    else
    {
        printf("\n");
        printf("Click on any key to start the next turn...\n");
        printf("\n");

        //TODO
        //ConsoleKeyInfo key = Console.ReadKey();
        StartTurn();
    }
}

int BattleField::GetRandomInt(int min, int max)
{
    
    int index = GetRandomInt(min, max);
    return index;
}

void BattleField::AlocatePlayers()
{
    AlocatePlayerCharacter();

}

void BattleField::AlocatePlayerCharacter()
{
    int random = 0;
    auto l_front = grid->grids.begin();
    advance(l_front, random);
    Types::GridBox* RandomLocation = &*l_front;

    if (!RandomLocation->ocupied)
    {
        //Types::GridBox* PlayerCurrentLocation = RandomLocation;
        PlayerCurrentLocation = &*l_front;
        l_front->ocupied = true;
        PlayerCharacter->currentBox = *l_front;
        AlocateEnemyCharacter();
    }
    else
    {
        AlocatePlayerCharacter();
    }
}

void BattleField::AlocateEnemyCharacter()
{
    
    int random = 24;
    auto l_front = grid->grids.begin();
    advance(l_front, random);
    Types::GridBox* RandomLocation = &*l_front;
    
    if (!RandomLocation->ocupied)
    {
        EnemyCurrentLocation = &*l_front;
        l_front->ocupied = true;
        EnemyCharacter->currentBox = *l_front;
        grid->drawBattlefield(5, 5);
    }
    else
    {
        AlocateEnemyCharacter();
    }


}