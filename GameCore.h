#pragma once
#include <string>
#include <vector>

namespace TextGame
{
	struct Position {
		int X;
		int Y;


		// Below is done so we can check if playerState.currentPosition == playerState.desiredPosition
		bool operator==(const Position& otherPosition) const {
			return X == otherPosition.X && Y == otherPosition.Y;
		}

		bool operator!=(const Position& otherPosition) const {
			return !(*this == otherPosition); // *this refers to the struct Position
		}
	};

	enum ItemType
	{
		ItemType_KEY,
		ItemType_SWORD
	};

	struct InvestoryItem {
		ItemType Type;
		Position ItemPosition;
	};

	struct PlayerState
	{
		bool WantsToExit;
		bool WantsDescription;
		bool WantsInventoryListed;
		
		Position CurrentPosition;
		Position DesiredPosition;

		int CurrentRoomIndex;

		std::vector<InvestoryItem> Inventory;
	};

	struct RoomData
	{
		std::string Name;
		std::string Description;

		int RoomMapWidth;
		std::string RoomMap;

		Position RoomPosition;
	};

	struct WorldState
	{
		std::vector<RoomData> Rooms;
	};

	void InitializeGame(PlayerState& playerState, WorldState& worldState);
	void GetInput(PlayerState& playerState, const WorldState& worldState);
	void RenderGame(const PlayerState& playerState, const WorldState& worldState);
	void UpdateGame(PlayerState& playerState, WorldState& worldState);
	void CleanupGame(PlayerState& playerState, WorldState& worldState);

	int PositionToIndex(const Position& position, int roomWidth);
	bool IsSpaceIsOpenForMovement(const Position& position, const RoomData& currRoom);
	bool IsSpaceOutsideMap(const Position& position, const RoomData& currRoom);

	std::string GetItemName(ItemType itemType);

}