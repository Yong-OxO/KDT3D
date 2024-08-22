#include "LoginSession.h"

FLoginSession* FLoginSession::Get(const bool bDestry)
{
	std::unique_ptr<FLoginSession> Instance{ new FLoginSession };
	if (bDestry) { Instance = nullptr; }
	return Instance.get();
}

FPlayer* FLoginSession::Login(const FAccount& InAccount, std::string_view InPlayerName, EErrorCode* const OptionalOutErrorCode)
{
	std::shared_ptr<FPlayer> Player = FDataBase::Get()->CheckPlayer(InAccount, InPlayerName, OptionalOutErrorCode);
	if (Player == nullptr) { return nullptr; }
	// @TODO : IsLogin이라면 LogOut 후 Login 진행

	std::pair Pair = PlayerMap.insert(std::make_pair(InAccount.ID, *Player.get()));
	if (Pair.second == false)
	{
		if(OptionalOutErrorCode) 
		{ 
			*OptionalOutErrorCode = EErrorCode::EUnknown;
			return nullptr;
		}
	}

	if (OptionalOutErrorCode) { *OptionalOutErrorCode = EErrorCode::ESuccessed; }

	return &(Pair.first)->second;
}

FPlayer* FLoginSession::IsLogin(const FAccountName& InAccountName)
{
	return nullptr;
}

FPlayer* FLoginSession::IsLogin(const FAccountName& InAccountName, std::string_view InPlayerName)
{
	return nullptr;
}

