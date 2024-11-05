#include "GameCore.h"
#include "CommandParser.h"
#include <stdio.h>
#include <cstring>
#include <string>
#include <vector>

namespace TextGame
{
	RoomData CreateRoom(const std::string& inName, const std::string& inDescription)
	{
		RoomData room = {};
		room.Name = inName;
		room.Description = inDescription;

		return room;
	}

	void InitializeGame(PlayerState& playerState, WorldState& worldState)
	{
		printf("Welcome to...\n");
		printf("A GAME by SOMEONE\n\n");
		printf("TELL THE PLAYER THE GOAL OF THE GAME\n\n");

		playerState.WantsDescription = true;
		playerState.CurrentRoomIndex = 0;

		worldState.Rooms.clear();

		// 0
		{
			RoomData room = CreateRoom("ROOM NAME", "ROOM DESCRIPTION");

			worldState.Rooms.push_back(room);
		}
	}

	void GetInput(PlayerState& playerState, const WorldState& worldState)
	{
		playerState.WantsToExit = false;
		playerState.WantsDescription = false;
		playerState.WantsInventoryListed = false;
		
		printf("What do you do?\n");
		printf("> ");
		TextAdventureCommand command = ParseAdventureCommand();

		if (command.Verb == "quit")
		{
			playerState.WantsToExit = true;
		}
		/*else if (command.Verb == "north" || command.Verb == "n")
		{
			
		}
		else if (command.Verb == "south" || command.Verb == "s")
		{
			
		}
		else if (command.Verb == "west" || command.Verb == "w")
		{
			
		}
		else if (command.Verb == "east" || command.Verb == "e")
		{
			
		}*/
		else if (command.Verb == "look")
		{
			playerState.WantsDescription = true;
		}
		else if (command.Verb == "inventory" || command.Verb == "inv")
		{
			playerState.WantsInventoryListed = true;
		}
		/*else if (command.Verb == "get")
		{
			
		}*/
		else if (command.Verb == "help")
		{
			printf("Command List: look, quit, inventory, get, north, south, west, east\n");
			printf("Key:\n");
			printf("  @ - Player\n");
			printf("  A - Altar\n");
			printf("  i - Item\n");
			printf("  . - Floor\n");
			printf("  # - Wall\n");
			printf("  H - Door (Locked)\n");
		}
		else
		{
			printf("I don't understand\n");
		}
		printf("\n");

	}

	void RenderGame(const PlayerState& playerState, const WorldState& worldState)
	{
		if (playerState.WantsDescription)
		{
			const RoomData& currRoom = worldState.Rooms[playerState.CurrentRoomIndex];
			printf("================================================\n");
			printf("LOCATION: %s\n", currRoom.Name.c_str());
			printf("%s\n\n", currRoom.Description.c_str());
			
			printf("\n");
		}
		else if (playerState.WantsInventoryListed)
		{
			printf("================================================\n");
			printf("INVENTORY:\n");

			printf("\n");
		}
	}

	void UpdateGame(PlayerState& playerState, WorldState& worldState)
	{
		RoomData& currRoom = worldState.Rooms[playerState.CurrentRoomIndex];
				
	}

	void CleanupGame(PlayerState& playerState, WorldState& worldState)
	{
		worldState.Rooms.clear();
	}
}
