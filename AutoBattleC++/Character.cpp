#include "Grid.h"
#include "Character.h"
#include "Types.h"
#include <vector>
#include <algorithm>



using namespace std;
Character::Character(Types::CharacterClass charcaterClass)
{
    Types::GridBox currentBox(0, 0, false, 0);
}

Character::~Character() 
{

}

void Character::TakeDamage(float amount) 
{
    Health = Health - amount;
	if (Health <= 0) 
	{
		Die();
	}
}

void Character::Die() 
{
    IsDead = true;

    if (PlayerIndex == 0)
    {
        printf("\nPlayer Died!\n");
    }
    else
    {
        printf("\nEnemy Died!\n");
    }
}



void Character::StartTurn(Grid* battlefield, bool IsPlayerTurn) {
    
    //Here we going to verify if the player is alive.
    if (target->target->Health <= 0)
    {
        IsDead = true;
        return;
    }

    //Look who the turn's from.
    if (PlayerIndex == 0)
    {
        printf("\nPlayer Action:\n");
    }
    else
    {
        printf("\nEnemy Action:\n");
    }


	if (CheckCloseTargets(battlefield)) //Checks if there is any Close Attack Target (Diagonals are not Considered)
	{

		Attack(&*target);

		return;
	}
	else
	{   // if there is no target close enough, calculates in wich direction this character should move to be closer to a possible target

		//Makes the Current Character Position Free because it will move
		battlefield->grids[(currentBox.xIndex * battlefield->xLenght) + currentBox.yIndex].ocupied = false;

		if (currentBox.xIndex > target->currentBox.xIndex)
		{
			//This make the character go up
			battlefield->grids[((currentBox.xIndex - 1) * battlefield->xLenght) + currentBox.yIndex].ocupied = true;

			if (IsPlayerTurn)
			{

				battlefield->PlayerCurrentLocation->xIndex = battlefield->PlayerCurrentLocation->xIndex - 1;
				currentBox = *battlefield->PlayerCurrentLocation;
			}
			else
			{
				battlefield->EnemyCurrentLocation->xIndex = battlefield->EnemyCurrentLocation->xIndex - 1;
				currentBox = *battlefield->EnemyCurrentLocation;
			}

			currentBox.ocupied = true;
			target->target->currentBox = currentBox;

			battlefield->drawBattlefield(5, 5);

			return;
		}
		else if (currentBox.xIndex < target->currentBox.xIndex)
		{
			//This make the character goe down
			battlefield->grids[((currentBox.xIndex + 1) * battlefield->xLenght) + currentBox.yIndex].ocupied = true;

			if (IsPlayerTurn)
			{
				battlefield->PlayerCurrentLocation->xIndex = battlefield->PlayerCurrentLocation->xIndex + 1;
				currentBox = *battlefield->PlayerCurrentLocation;
			}
			else
			{
				battlefield->EnemyCurrentLocation->xIndex = battlefield->EnemyCurrentLocation->xIndex + 1;
				currentBox = *battlefield->EnemyCurrentLocation;
			}

			currentBox.ocupied = true;
			target->target->currentBox = currentBox;

			battlefield->drawBattlefield(5, 5);

			return;
		}

		if (currentBox.yIndex > target->currentBox.yIndex)
		{
			//This make the character go left
			battlefield->grids[(currentBox.xIndex * battlefield->xLenght) + (currentBox.yIndex - 1)].ocupied = true;

			if (IsPlayerTurn)
			{
				battlefield->PlayerCurrentLocation->yIndex = battlefield->PlayerCurrentLocation->yIndex - 1;
				currentBox = *battlefield->PlayerCurrentLocation;
			}
			else
			{
				battlefield->EnemyCurrentLocation->yIndex = battlefield->EnemyCurrentLocation->yIndex - 1;
				currentBox = *battlefield->EnemyCurrentLocation;
			}

			currentBox.ocupied = true;
			target->target->currentBox = currentBox;

			battlefield->drawBattlefield(5, 5);

			return;

		}
		else if (currentBox.yIndex < target->currentBox.yIndex)
		{
			//This make the character go right

			battlefield->grids[(currentBox.xIndex * battlefield->xLenght) + (currentBox.yIndex + 1)].ocupied = true;

			if (IsPlayerTurn)
			{
				battlefield->PlayerCurrentLocation->yIndex = battlefield->PlayerCurrentLocation->yIndex + 1;
				currentBox = *battlefield->PlayerCurrentLocation;
			}
			else
			{
				battlefield->EnemyCurrentLocation->yIndex = battlefield->EnemyCurrentLocation->yIndex + 1;
				currentBox = *battlefield->EnemyCurrentLocation;
			}

			currentBox.ocupied = true;
			target->target->currentBox = currentBox;

			battlefield->drawBattlefield(5, 5);

			return;
		}



	}
}

bool Character::CheckCloseTargets(Grid* battlefield)
{
	currentBox.xIndex = target->target->currentBox.xIndex;
	currentBox.yIndex = target->target->currentBox.yIndex;

	//verify top. if not move top.
	if (battlefield->grids[((currentBox.xIndex) * battlefield->xLenght) + currentBox.yIndex].xIndex != 0)
	{
		if (battlefield->grids[((currentBox.xIndex - 1) * battlefield->xLenght) + currentBox.yIndex].ocupied == true)
		{
			printf("Found a Target at the Top \n");
			return true;
		}
	}


	//verify bot. if not move down.
	if (battlefield->grids[((currentBox.xIndex) * battlefield->xLenght) + currentBox.yIndex].xIndex != (battlefield->xLenght - 1))
	{
		if (battlefield->grids[((currentBox.xIndex + 1) * battlefield->xLenght) + currentBox.yIndex].ocupied == true)
		{
			printf("Found a Target at the Bottom \n");
			return true;
		}
	}

	//verify left. if not move left.
	if (battlefield->grids[((currentBox.xIndex) * battlefield->xLenght) + currentBox.yIndex].yIndex != 0)
	{
		if (battlefield->grids[(currentBox.xIndex * battlefield->xLenght) + (currentBox.yIndex - 1)].ocupied == true)
		{
			printf("Found a Target at the Left \n");
			return true;
		}
	}

	//verify right. if not move right.

	if (battlefield->grids[((currentBox.xIndex) * battlefield->xLenght) + currentBox.yIndex].yIndex != (battlefield->yLength - 1))
	{
		if (battlefield->grids[(currentBox.xIndex * battlefield->xLenght) + (currentBox.yIndex + 1)].ocupied == true)
		{
			printf("Found a Target at the Right \n");
			return true;
		}
	}

	return false;
}

void Character::Attack(Character* target) 
{
	if (PlayerIndex == 0)
	{
		printf("The Player attacks the Enemy!\n");
	}
	else
	{
		printf("The Enemy attacks the Player!\n");
	}

	target->TakeDamage(BaseDamage * DamageMultiplier);
}

