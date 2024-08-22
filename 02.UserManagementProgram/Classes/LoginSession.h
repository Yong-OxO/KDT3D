#pragma once
#include "DataBase.h"

class FLoginSession
{
public:
	static FLoginSession* Get(const bool bDestry = false);

	~FLoginSession();
public:
	FPlayer* Login(const FAccount& InAccount, std::string_view InPlayerName, EErrorCode* const OptionalOutErrorCode = nullptr);

	FPlayer* IsLogin(const FAccountName& InAccountName);
	FPlayer* IsLogin(const FAccountName& InAccountName, std::string_view InPlayerName);

	EErrorCode Logout(const FAccount& InAccount, std::string_view InPlayerName);
	const std::unordered_map<FAccountName, FPlayer>& GetPlayers() const { return PlayerMap; }

private:
	FLoginSession() = default;
	FLoginSession(const FLoginSession&) = delete;
	FLoginSession& operator=(const FLoginSession&) = delete;

	EErrorCode Logout(const FAccount& InAccount);

	void AllPlayerLogout();

private:
	std::unordered_map<FAccountName, FPlayer> PlayerMap;
};

