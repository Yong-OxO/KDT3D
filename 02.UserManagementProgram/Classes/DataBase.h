#pragma once
#include "Misc/Headers.h"
#include "Classes/Account.h"
//#include "Classes/Player.h"

class FDataBase
{
public:
	static FDataBase* Get(const bool bDestry = false);

public:
	FAccount* CreateAccount(const FAccount& InAccount, EErrorCode* const OptionalOutErrorCode = nullptr, const bool bSaveToFile = true);
	EErrorCode DeleteAccount(const FAccount& InAccount);

	// ID를 이용해 존재하는지 조회
	FAccount* FindAccount(const FAccountName& InID);
	// 입력 계정(ID PW)를 조회해 기존 정보와 일치하는지 조회
	FAccount* CheckAccount(const FAccount& InAccount, EErrorCode* const OptionalOutErrorCode = nullptr, const bool bSaveToFile = true);

	const std::unordered_map<FAccountName, FAccount>& GetAccounts() const { return AccountMap; }
protected:
	void SaveAccountFile(const FAccount& InAccount);

private:

private:
	static inline const std::string AccountsDirectory = "Accounts";
	std::unordered_map<FAccountName, FAccount> AccountMap;
};

