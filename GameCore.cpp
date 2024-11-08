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
		playerState.CurrentPosition.X = 4;
		playerState.CurrentPosition.Y = 2;

		worldState.Rooms.clear();

		// 1
		{
			RoomData room = CreateRoom("ROOM NAME 1", "ROOM DESCRIPTION 1");
			room.RoomMapWidth = 8;
			room.RoomPosition = { 0, 0 };
			room.RoomMap = 
				"########"
				"#......#"
				"#......#"
				"#......#"
				"#......#"
				"#......#"
				"###..###";

			worldState.Rooms.push_back(room);
		}

		// 2
		{
			RoomData room = CreateRoom("ROOM NAME 2", "ROOM DESCRIPTION 2");
			room.RoomMapWidth = 8;
			room.RoomPosition = { 0, 1 };
			room.RoomMap =
				"###..###"
				"#......#"
				"#......#"
				"#......."
				"#......#"
				"#......#"
				"########";

			worldState.Rooms.push_back(room);
		}

		// 3
		{
			RoomData room = CreateRoom("ROOM NAME 3", "ROOM DESCRIPTION 3");
			room.RoomMapWidth = 8;
			room.RoomPosition = { 1, 1 };
			room.RoomMap =
				"###..###"
				"#......#"
				"#..##..#"
				"...##..."
				"#..##..#"
				"#......#"
				"###..###";

			worldState.Rooms.push_back(room);
		}

		// 4 (up)
		{
			RoomData room = CreateRoom("ROOM NAME 4", "ROOM DESCRIPTION 4");
			room.RoomMapWidth = 8;
			room.RoomPosition = { 1, 0 };
			room.RoomMap =
				"########"
				"#......#"
				"#......#"
				"#......#"
				"#......#"
				"#......#"
				"###..###";

			worldState.Rooms.push_back(room);
		}
		// 5 (down)
		{
			RoomData room = CreateRoom("ROOM NAME 5", "ROOM DESCRIPTION 5");
			room.RoomMapWidth = 8;
			room.RoomPosition = { 1, 2 };
			room.RoomMap =
				"###..###"
				"#......#"
				"#......#"
				"#......#"
				"#......#"
				"#......#"
				"########";

			worldState.Rooms.push_back(room);
		}
		// 6 (right)
		{
			RoomData room = CreateRoom("ROOM NAME 6", "ROOM DESCRIPTION 6");
			room.RoomMapWidth = 8;
			room.RoomPosition = { 2, 1 };
			room.RoomMap =
				"########"
				"#......#"
				"#......#"
				"........"
				"#......#"
				"#......#"
				"########";

			worldState.Rooms.push_back(room);
		}

		// 7
		{
			RoomData room = CreateRoom("ROOM NAME 7", "ROOM DESCRIPTION 7");
			room.RoomMapWidth = 8;
			room.RoomPosition = { 3, 1 };
			room.RoomMap =
				"########"
				"#......#"
				"#......#"
				".......#"
				"#......#"
				"#......#"
				"###..###";

			worldState.Rooms.push_back(room);
		}

		// 8
		{
			RoomData room = CreateRoom("ROOM NAME 8", "ROOM DESCRIPTION 8");
			room.RoomMapWidth = 8;
			room.RoomPosition = { 3, 2 };
			room.RoomMap =
				"###..###"
				"#......#"
				"#......#"
				"#......."
				"#......#"
				"#......#"
				"########";

			worldState.Rooms.push_back(room);
		}

		// 9
		{
			RoomData room = CreateRoom("ROOM NAME 9", "ROOM DESCRIPTION 9");
			room.RoomMapWidth = 8;
			room.RoomPosition = { 4, 2 };
			room.RoomMap =
				"########"
				"#......#"
				"#......#"
				".......#"
				"#......#"
				"#......#"
				"########";

			worldState.Rooms.push_back(room);
		}
	}

	void GetInput(PlayerState& playerState, const WorldState& worldState)
	{
		playerState.WantsToExit = false;
		playerState.WantsDescription = false;
		playerState.WantsInventoryListed = false;
		playerState.DesiredPosition = playerState.CurrentPosition;
		
		printf("What do you do?\n");
		printf("> ");
		TextAdventureCommand command = ParseAdventureCommand();

		if (command.Verb == "quit")
		{
			playerState.WantsToExit = true;
		}
		else if (command.Verb == "north" || command.Verb == "n")
		{
			playerState.DesiredPosition.Y = playerState.CurrentPosition.Y - 1;
		}
		else if (command.Verb == "south" || command.Verb == "s")
		{
			playerState.DesiredPosition.Y = playerState.CurrentPosition.Y + 1;
		}
		else if (command.Verb == "west" || command.Verb == "w")
		{
			playerState.DesiredPosition.X = playerState.CurrentPosition.X - 1;
		}
		else if (command.Verb == "east" || command.Verb == "e")
		{
			playerState.DesiredPosition.X = playerState.CurrentPosition.X + 1;
		}
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
			
			std::string renderedMapString = "";
			unsigned int currentSpace = 0;
			while (currentSpace < currRoom.RoomMap.size()) {
				char characterToDisplay = currRoom.RoomMap[currentSpace];

				// if player is here, replace characterToDisplay with @
				if (PositionToIndex(playerState.CurrentPosition, currRoom.RoomMapWidth) == currentSpace ) {
					characterToDisplay = '@';
				}
				

				// if an item is here, replace characterToDisplay with i



				renderedMapString += characterToDisplay;
				if (currentSpace % currRoom.RoomMapWidth == (currRoom.RoomMapWidth - 1) ) { // % is modulus, giving a remainder
					renderedMapString += "\n";
				}


				currentSpace++;
			}


			printf("%s\n", renderedMapString.c_str());

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
				
		if (playerState.CurrentPosition != playerState.DesiredPosition ) { // this works because of Struct in GameCore.h
			if (IsSpaceOutsideMap(playerState.DesiredPosition,currRoom)) {

				Position desiredRoomPosition = currRoom.RoomPosition;
				int playerPositionType = 0;

				if (playerState.DesiredPosition.X < 0) 
				{
					desiredRoomPosition.X--;
					playerPositionType = 1; // w
				} 
				else if (playerState.DesiredPosition.X >= currRoom.RoomMapWidth) {
					desiredRoomPosition.X++;
					playerPositionType = 2; // e
				}
				else if (playerState.DesiredPosition.Y < 0)
				{
					desiredRoomPosition.Y--;
					playerPositionType = 3; // n
				}
				else if (playerState.DesiredPosition.Y >= ((int)currRoom.RoomMap.size() / currRoom.RoomMapWidth))
				{
					desiredRoomPosition.Y++; 
					playerPositionType = 4; // s
				}

				bool foundNewRoom = false;
				for (unsigned int i = 0; i < worldState.Rooms.size(); ++i) {
					if (worldState.Rooms[i].RoomPosition == desiredRoomPosition ) {
						playerState.CurrentRoomIndex = i;
						playerState.WantsDescription = true;

						switch (playerPositionType)
						{
						case 1: // w
							playerState.CurrentPosition.X = worldState.Rooms[playerState.CurrentRoomIndex].RoomMapWidth - 1;
							break;
						case 2: // e
							playerState.CurrentPosition.X = 0;
							break;
						case 3: // n
							playerState.CurrentPosition.Y = (worldState.Rooms[playerState.CurrentRoomIndex].RoomMap.size() / worldState.Rooms[playerState.CurrentRoomIndex].RoomMapWidth) - 1;
							break;
						case 4: // s
							playerState.CurrentPosition.Y = 0;
							break;
						}

						foundNewRoom = true;
					}
				}

				if (!foundNewRoom) {
					printf("nothing but void out there!\n\n");
				}

			}
			else if (IsSpaceIsOpenForMovement(playerState.DesiredPosition, currRoom)) 
			{
				playerState.CurrentPosition = playerState.DesiredPosition;
				playerState.WantsDescription = true;
			}
			else 
			{
				printf("That path is blocked!\n");
			}
		}

	}

	void CleanupGame(PlayerState& playerState, WorldState& worldState)
	{
		worldState.Rooms.clear();
	}

	int PositionToIndex(const Position& position, int roomWidth) {
		return position.Y * roomWidth + position.X;
	}

	bool IsSpaceIsOpenForMovement(const Position& position, const RoomData& currRoom) {
		int spaceToIndex = PositionToIndex(position,currRoom.RoomMapWidth);
		return currRoom.RoomMap[spaceToIndex] == '.';
	}

	bool IsSpaceOutsideMap(const Position& position, const RoomData& currRoom) {
		return position.X < 0 ||
			position.X >= currRoom.RoomMapWidth ||
			position.Y < 0 ||
			position.Y >= ((int)currRoom.RoomMap.size() / currRoom.RoomMapWidth);
	}
}
