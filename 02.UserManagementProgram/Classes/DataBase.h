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
	FAccount* FindAccount(const FAccountName& InID);

	const std::unordered_map<FAccountName, FAccount>& GetAccounts() const { return AccountMap; }
protected:
	void SaveAccountFile(const FAccount& InAccount);

private:

private:
	static inline const std::string AccountsDirectory = "Accounts";
	std::unordered_map<FAccountName, FAccount> AccountMap;
};

