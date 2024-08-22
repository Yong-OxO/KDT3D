#pragma once
#include "Misc/Headers.h"
#include "Classes/Account.h"
class FPlayer
{
public:
	FPlayer() = default;
	FPlayer(FAccountName InAccountName, std::string_view InPlayerName, unsigned int InLevel)
		: AccountName(InAccountName),
		PlayerName(InPlayerName),
		Level(InLevel)
	{}

	void OnLogout()
	{
		std::cout << std::format("Player OnLogout: {}, {}, Lv.{}\n", AccountName, PlayerName, Level);
	}

	std::string_view GetAccountName() const;
	std::string_view GetPlayerName() const { return PlayerName; };
	int GetLevel() const { return Level; }
	
	void Save(rapidjson::Value& OutValue, rapidjson::Document::AllocatorType& InAllocator);
	bool Load(const rapidjson::Value& InValue);

	void LevelUp() { ++Level; }


private:
	FAccountName AccountName;
	std::string PlayerName;
	unsigned int Level = 1;
};

