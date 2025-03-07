#include "valley.h"

PlayerStruct * playerSetup()
{
	PlayerStruct * player = malloc(sizeof(PlayerStruct));
	player->skin = '@'; // Set player char
	player->inventory_size = 3;
	initPlayerInventory(player);
	player->max_health = PLAYER_MAX_HEALTH;
	player->health = player->max_health;
	player->base_attack = PLAYER_BASE_ATTACK;
	player->attack = player->base_attack;

	return player;
}

void initPlayerInventory(PlayerStruct * player)
{
	int size = player->inventory_size;
	player->inventory = malloc(sizeof(Item*) * size);


    for(int i = 0; i < size; i++)
    {
        player->inventory[i] = malloc(sizeof(Item));
		player->inventory[i] = NULL;
    }
}

void setRandomSpawn(Game * game)
{
	Position random;
	do {
		random.y = rand() % (game->map->dimensions.height - 2) + 1;
		random.x = rand() % (game->map->dimensions.width - 2) + 1;
	} while (game->map->tiles[random.y][random.x] == '#' || game->map->tiles[random.y][random.x] == '.');

	game->player->position.y = random.y;
	game->player->position.x = random.x;
}


Position handleInput(int input) 
{
	Position position_offset;

	position_offset.y = 0;
	position_offset.x = 0;

	switch(input) 
	{
		case 'z' :
		case 'Z' :
			position_offset.y = - 1;
			position_offset.x = 0;
			break;
		case 's' :
		case 'S' :
			position_offset.y = + 1;
			position_offset.x = 0;
			break;
		case 'q' :
		case 'Q' :
			position_offset.y = 0;
			position_offset.x = - 1;
			break;
		case 'd' :
		case 'D' :
			position_offset.y = 0;
			position_offset.x = + 1;
			break;

		default :
			break;	
	}
	return position_offset;
}


void checkPosition(Position position_offset, Game * game, Windows * windows)
{
	Position new;
	new.y = game->player->position.y + position_offset.y;
    new.x = game->player->position.x + position_offset.x;

	if (new.y >= 0 && new.y < game->map->dimensions.height && new.x >= 0 && new.x < game->map->dimensions.width)
    {
    	switch (game->map->tiles[game->player->position.y + position_offset.y][game->player->position.x + position_offset.x])
    	{
     		case 'X': // If moves towards an enemy
    	    case 'G':
    	    case 'T':
     	    	//combat(...);
				break;
			case 'W':
				ManageWizardInteractions(game, windows);
				break;
    	    default: // If else
				playerMove(position_offset, game); // Manage how to move the player
    	        break;
		}
	}
}


void playerMove(Position position_offset, Game * game)
{
	Position new_position;

	new_position.y = game->player->position.y + position_offset.y;
	new_position.x = game->player->position.x + position_offset.x;



	switch (game->map->tiles[new_position.y][new_position.x])
	{
		case '%':
		case '#': // If not crossable
		case '.':
		case 'W':
			break;
		case 'O': // If movable
			//handleMovable();
		break;
		default: // If crossable
			game->player->position = new_position;
			break;
	}
}