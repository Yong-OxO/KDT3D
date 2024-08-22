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

	FAccountName GetAccountName();
	std::string GetPlayerName();
	void Save(rapidjson::Value& OutValue, rapidjson::Document::AllocatorType& InAllocator);
	bool Load(const rapidjson::Value& InValue);


private:
	FAccountName AccountName;
	std::string PlayerName;
	unsigned int Level = 1;
};

