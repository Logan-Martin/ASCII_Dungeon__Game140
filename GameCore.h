#pragma once
#include <string>
#include <vector>

namespace TextGame
{
	struct PlayerState
	{
		bool WantsToExit;
		bool WantsDescription;
		bool WantsInventoryListed;
		
		int CurrentRoomIndex;
	};

	struct RoomData
	{
		std::string Name;
		std::string Description;
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
}