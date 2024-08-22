#pragma once
#include "Misc/Headers.h"

using FAccountName = std::string;
struct FAccount
{
	FAccountName ID;
	std::string Password;

	FAccount() = default;
	FAccount(FAccountName InID, std::string InPassword)
		: ID(InID),
		Password(InPassword)
	{}

	bool IsEmpty() const
	{
		const bool bId = ID.empty();
		const bool bPw = Password.empty();

		return bId || bPw;
	}

	bool operator==(const FAccount& InAccount) const
	{
		// 계정이 비어 있는 경우 같지 않다고 취급
		const bool bEmpty = IsEmpty();
		if (bEmpty) { return false; }

		const bool bID = ID == InAccount.ID;
		const bool bPassword = Password == InAccount.Password;

		return bID && bPassword;
	} 
	bool operator!=(const FAccount& InAccount) const
	{
		return !(*this == InAccount);
	}
};
