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

	{
		FPlayer* Player = IsLogin(InAccount.ID);
		if (Player != nullptr)
		{
			EErrorCode ErrorCode = Logout(InAccount);
			if (ErrorCode != EErrorCode::ESuccessed)
			{
				_ASSERT(false);
				if (OptionalOutErrorCode) { *OptionalOutErrorCode = ErrorCode; }
				return nullptr;
			}

			Player = nullptr;
		}
	}
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
	auto It = PlayerMap.find(InAccountName);

	// 로그인 하지 않았다
	if (It == PlayerMap.end()) { return nullptr; }

	return &It->second;
}

FPlayer* FLoginSession::IsLogin(const FAccountName& InAccountName, std::string_view InPlayerName)
{
	FPlayer* Player = IsLogin(InAccountName);

	if (Player == false) { return nullptr; }
	if (Player->GetPlayerName() != InPlayerName) { return nullptr; }

	return Player;
}

EErrorCode FLoginSession::Logout(const FAccount& InAccount, std::string_view InPlayerName)
{
	EErrorCode ErrorCode;
	{
		std::shared_ptr<FPlayer> Player = FDataBase::Get()->CheckPlayer(InAccount, InPlayerName, &ErrorCode);
		if (ErrorCode != EErrorCode::ESuccessed) { return ErrorCode; }
	}

	FPlayer* Player = IsLogin(InAccount.ID, InPlayerName);
	if (Player == nullptr)
	{
		ErrorCode = EErrorCode::ENoLogin;
		return ErrorCode;
	}
	
	Player->OnLogout();
	FDataBase::Get()->SavePlayer(Player);
	PlayerMap.erase(InAccount.ID);

	return ErrorCode;
}


