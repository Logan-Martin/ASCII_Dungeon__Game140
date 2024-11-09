#include "GameCore.h"
#include "CommandParser.h"
#include <stdio.h>
#include <cstring>
#include <string>
#include <vector>
#include <conio.h>

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
		printf("The ASCII Dungeon by Logan Martin\n\n");
		printf("The goal is to find and get the relic stone!\n\n");

		playerState.WantsDescription = true;
		playerState.CurrentRoomIndex = 0;
		playerState.CurrentPosition.X = 4;
		playerState.CurrentPosition.Y = 2;
		playerState.WantsToGet = false;

		//playerState.Inventory.push_back({ ItemType_KEY, Position() });
		//playerState.Inventory.push_back({ ItemType_SWORD, Position() });
		//playerState.Inventory.push_back({ ItemType_KEY, Position() });


		worldState.Rooms.clear();

		// 1
		{
			RoomData room = CreateRoom("The Starting Field", "An empty grass field with a few flowers. Trees surround the area.");
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
			RoomData room = CreateRoom("Small rock field", "There are some small rocks dotted about, not much difference from just above.");
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
			RoomData room = CreateRoom("Random Wall Junction", "There are 3 new paths to take. A wall of stone sits in the middle of the field.");
			room.RoomMapWidth = 8;
			room.RoomPosition = { 1, 1 };
			room.RoomMap =
				"###..###"
				"#......#"
				"#......#"
				"...##..."
				"#......#"
				"#......#"
				"###..###";

			worldState.Rooms.push_back(room);
		}

		// 4 (up)
		{
			RoomData room = CreateRoom("Small Cave", "You enter a small cave with a few items on the floor.");
			room.RoomMapWidth = 8;
			room.RoomPosition = { 1, 0 };
			room.RoomMap =
				"########"
				"##....##"
				"#......#"
				"#......#"
				"#......#"
				"##....##"
				"###..###";

			room.Inventory.push_back({ ItemType_KEY, {2,3} }); 
			room.Inventory.push_back({ ItemType_SWORD, {2,2} });

			worldState.Rooms.push_back(room);

		}
		// 5 (down)
		{
			RoomData room = CreateRoom("Empty Field 2", "Another empty grass field, maybe there are some items somewhere else.");
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
			RoomData room = CreateRoom("Small Grassy Pathway", "This pathway is narrow. A door is at the end. I wonder where it leads.");
			room.RoomMapWidth = 8;
			room.RoomPosition = { 2, 1 };
			room.RoomMap =
				"########"
				"########"
				"#......#"
				"........"
				"#......#"
				"########"
				"########";

			room.LookedDoors.push_back({ {7,3} });

			worldState.Rooms.push_back(room);
		}

		// 7
		{
			RoomData room = CreateRoom("Another Grass Field", "Another grass field huh. There's a big rock and up ahead, sounds exciting.");
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
			RoomData room = CreateRoom("Big Cave Entrance", "This cave has more to it than the last one.");
			room.RoomMapWidth = 8;
			room.RoomPosition = { 3, 2 };
			room.RoomMap =
				"###..###"
				"##...###"
				"#....###"
				"#..###.."
				"#...#..#"
				"##....##"
				"########";

			worldState.Rooms.push_back(room);
		}

		// 9
		{
			RoomData room = CreateRoom("Big Cave End", "There's a Relic Stone at the center, not much else.");
			room.RoomMapWidth = 8;
			room.RoomPosition = { 4, 2 };
			room.RoomMap =
				"########"
				"##....##"
				"#......#"
				".......#"
				"#......#"
				"##....##"
				"########";
			room.Inventory.push_back({ ItemType_RELICSTONE, {4,3} });
			worldState.Rooms.push_back(room);
		}
	}

	void GetInput(PlayerState& playerState, const WorldState& worldState)
	{
		playerState.WantsToExit = false;
		playerState.WantsDescription = false;
		playerState.WantsInventoryListed = false;
		playerState.DesiredPosition = playerState.CurrentPosition;
		
		printf("What do you do? (press 'c' for Command Mode & type 'help' for a command list)\n");
		printf("> ");
		TextAdventureCommand command = {};
		command.Verb = "";

		while (command.Verb == "") {
			char key = _getch();

			if (key == 'A' || key == 'a') command.Verb = 'w';
			else if (key == 'W' || key == 'w') command.Verb = "n";
			else if (key == 'S' || key == 's') command.Verb = "s";
			else if (key == 'D' || key == 'd') command.Verb = "e";
			else if (key == 'C' || key == 'c') command.Verb = "commandMode";
		}

		if (command.Verb == "commandMode") {
			printf("Command Mode: ");
			command = ParseAdventureCommand();
		}

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
		else if (command.Verb == "get")
		{
			playerState.WantsToGet = true;
		}
		else if (command.Verb == "help")
		{
			printf("Command List: look, quit, inventory, get, north (w), south (s), west (a), east (d) \n");
			printf("Key:\n");
			printf("  @ - Player\n");
			printf("  0 - Relic Stone\n");
			printf("  k - Key \n");
			printf("  s - Sword \n");
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

				// if an item is here, replace characterToDisplay with i
				for (unsigned int i = 0; i < currRoom.Inventory.size(); ++i) {
					const InventoryItem& currItem = currRoom.Inventory[i];
					if (PositionToIndex(currItem.ItemPosition, currRoom.RoomMapWidth) == currentSpace) {
						characterToDisplay = GetItemIcon(currItem.Type) ;
					}
				}

				// For Locked Doors:
				for (unsigned int i = 0; i < currRoom.LookedDoors.size(); ++i) {
					const LockedDoorData& currDoor = currRoom.LookedDoors[i];
					if (PositionToIndex(currDoor.DoorPosition, currRoom.RoomMapWidth) == currentSpace) {
						characterToDisplay = 'D';
					}
				}

				// if player is here, replace characterToDisplay with @
				if (PositionToIndex(playerState.CurrentPosition, currRoom.RoomMapWidth) == currentSpace ) {
					characterToDisplay = '@';
				}
				


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

			if (playerState.Inventory.size() == 0) {
				printf("You have nothing in your inventory!\n");
			}
			else {
				for (unsigned int i = 0; i < playerState.Inventory.size(); i++) {
					printf("%s\n", GetItemName(playerState.Inventory[i].Type).c_str());
				}

			}

			printf("\n");
		}
	}

	void UpdateGame(PlayerState& playerState, WorldState& worldState)
	{
		RoomData& currRoom = worldState.Rooms[playerState.CurrentRoomIndex];
				
		if (playerState.DesiredPosition != playerState.CurrentPosition ) { // this works because of Struct in GameCore.h

			TryToUnlockDoor(playerState.DesiredPosition,currRoom, playerState);


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
					int valueToPrint = ((int)currRoom.RoomMap.size() / currRoom.RoomMapWidth);
					desiredRoomPosition.Y++; 
					playerPositionType = 4; // s
				}

				bool foundNewRoom = false;
				for (unsigned int i = 0; i < worldState.Rooms.size(); ++i) 
				{
					if (worldState.Rooms[i].RoomPosition == desiredRoomPosition) 
					{
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
				printf("\nThat path is blocked!\n");
			}
		}
		else if (playerState.WantsToGet) {

			bool foundItem = false;
			for (unsigned int i = 0; i < currRoom.Inventory.size(); ++i) {
				const InventoryItem& currItem = currRoom.Inventory[i];
				if (currItem.ItemPosition == playerState.CurrentPosition) {

					if (currItem.Type == ItemType_RELICSTONE) {
						printf("\n\nYou got a '%s'and won the game!\n", GetItemName(currItem.Type).c_str());
						printf("Thanks for playing! \n\n");
						playerState.WantsToExit = true;
					}
					else
					{
						printf("\n You got a '%s'!\n", GetItemName(currItem.Type).c_str());
					}

					playerState.Inventory.push_back(currItem);
					currRoom.Inventory.erase(currRoom.Inventory.begin() + i);

					foundItem = true;
					break;
				}
			}

			if (!foundItem) {
				printf("\nThere is nothing there to get. \n");
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
		for (unsigned int i = 0; i < currRoom.LookedDoors.size(); ++i) {
			const LockedDoorData& currDoor = currRoom.LookedDoors[i];
			if (currDoor.DoorPosition == position) {
				return false;
			}
		}
		
		
		int spaceToIndex = PositionToIndex(position,currRoom.RoomMapWidth);
		return currRoom.RoomMap[spaceToIndex] == '.';
	}

	bool IsSpaceOutsideMap(const Position& position, const RoomData& currRoom) {
		return position.X < 0 ||
			position.X >= currRoom.RoomMapWidth ||
			position.Y < 0 ||
			position.Y >= ((int)currRoom.RoomMap.size() / currRoom.RoomMapWidth);
	}

	void TryToUnlockDoor(const Position& position, RoomData& currRoom, PlayerState& playerState) {
		for (unsigned int i_inv = 0; i_inv < currRoom.LookedDoors.size(); ++i_inv) {
			const LockedDoorData& currDoor = currRoom.LookedDoors[i_inv];
			if (currDoor.DoorPosition == position) {
				// We found a door, now found if they have a key

				bool doesPlayerHaveKeyToOpenDoor = false;
				for (unsigned int i_lockedDoors = 0; i_lockedDoors < playerState.Inventory.size(); ++i_lockedDoors) {
					const InventoryItem& currItem = playerState.Inventory[i_lockedDoors];
					if (currItem.Type == ItemType_KEY) {
						// Found a key!

						printf("\n You unlocked the door using your key. \n");
						doesPlayerHaveKeyToOpenDoor = true;
						currRoom.LookedDoors.erase(currRoom.LookedDoors.begin() + i_inv);
						playerState.Inventory.erase(playerState.Inventory.begin() + i_lockedDoors );
						return;
					}
				}

				if (!doesPlayerHaveKeyToOpenDoor) {
					printf("\n You don't have a key to unlock the door! \n");
				}

			}
		}
	}

	std::string GetItemName(ItemType itemType) {
		switch (itemType)
		{
		case ItemType_KEY:
			return "Shiny Key";
			break;
		case ItemType_SWORD:
			return "Rusty Sword";
			break;
		case ItemType_RELICSTONE:
			return "Relic Stone";
			break;

		}
		return "Unknown Item";
	}

	char GetItemIcon(ItemType itemType) {
		switch (itemType)
		{
		case TextGame::ItemType_KEY:
			return 'k';
			break;
		case TextGame::ItemType_SWORD:
			return 's';
			break;
		case ItemType_RELICSTONE:
			return '0';
			break;
		}
		return 'i';
	}


}
