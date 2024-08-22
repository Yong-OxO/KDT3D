#pragma once
#include "Misc/Headers.h"
#include "Classes/Account.h"
#include "Classes/Player.h"

class FDataBase
{
public:
	static FDataBase* Get(const bool bDestry = false);

public:
	FAccount* CreateAccount(const FAccount& InAccount, EErrorCode* const OptionalOutErrorCode = nullptr, const bool bSaveToFile = true);
	EErrorCode DeleteAccount(const FAccount& InAccount);

	EErrorCode CreatePlayer(const FAccount& InAccount, std::string_view InPlayerName);
	EErrorCode DeletePlayer(const FAccount& InAccount, std::string_view InPlayerName);
	std::shared_ptr<FPlayer> CheckPlayer(const FAccount& InAccount, std::string_view InPlayerName, EErrorCode* const OptionalOutErrorCode = nullptr);

	// ID를 이용해 존재하는지 조회
	FAccount* FindAccount(const FAccountName& InID);
	// 입력 계정(ID PW)를 조회해 기존 정보와 일치하는지 조회
	FAccount* CheckAccount(const FAccount& InAccount, EErrorCode* const OptionalOutErrorCode = nullptr);

	const std::unordered_map<FAccountName, FAccount>& GetAccounts() const { return AccountMap; }
protected:
	void SaveAccountFile(const FAccount& InAccount);
	void DeleteAccountFile(const FAccount& InAccount);
	void SavePlayer(FPlayer* InPlayer);


private:
	static inline const std::string AccountsDirectory = "Accounts";
	std::unordered_map<FAccountName, FAccount> AccountMap;

private:
	FDataBase();
};

