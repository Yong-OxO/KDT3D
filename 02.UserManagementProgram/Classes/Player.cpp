#include "Player.h"

FAccountName FPlayer::GetAccountName()
{
	return AccountName;
}

std::string FPlayer::GetPlayerName()
{
	return PlayerName;
}

void FPlayer::Save(rapidjson::Value& OutValue, rapidjson::Document::AllocatorType& InAllocator)
{
	OutValue.AddMember("AccountName", rapidjson::StringRef(AccountName.c_str()), InAllocator);
	OutValue.AddMember("PlayerName", rapidjson::StringRef(PlayerName.c_str()), InAllocator);
	OutValue.AddMember("Level", Level, InAllocator);
}

bool FPlayer::Load(const rapidjson::Value& InValue)
{
	const bool bAccountName = InValue.HasMember("AccountName");
	const bool bPlayerName = InValue.HasMember("PlayerName");
	const bool bLevel = InValue.HasMember("Level");
	if (!bAccountName || !bPlayerName || !bLevel) { return false; }

	AccountName = InValue["AccountName"].GetString();
	PlayerName = InValue["PlayerName"].GetString();
	Level = InValue["Level"].GetUint();

	return true;
}
