#include "DataBase.h"

FDataBase* FDataBase::Get(const bool bDestry)
{
	static std::unique_ptr<FDataBase> Instance = std::make_unique<FDataBase>();
	if (bDestry) { Instance = nullptr; }
	return Instance.get();
}

FAccount* FDataBase::CreateAccount(const FAccount& InAccount, EErrorCode* const OptionalOutErrorCode, const bool bSaveToFile)
{
	if (InAccount.IsEmpty())
	{
		if (OptionalOutErrorCode) { *OptionalOutErrorCode = EErrorCode::EEmptyAccount; }
		return nullptr;
	}
	FAccount* FoundAccount = FindAccount(InAccount.ID);
	// Account exists
	if (FoundAccount != nullptr)
	{
		if (OptionalOutErrorCode) { *OptionalOutErrorCode = EErrorCode::EDuplicateAccount; }
		return nullptr;
	}

	// insert의 반환값은 <iterator, bool>
	std::pair Pair = AccountMap.insert(std::make_pair(InAccount.ID, InAccount));
	if (Pair.second == false)
	{
		_ASSERT(false);
		if (OptionalOutErrorCode) { *OptionalOutErrorCode = EErrorCode::EUnknown; }
		return nullptr;
	}

	if (OptionalOutErrorCode) { *OptionalOutErrorCode = EErrorCode::ESuccessed; }

	if (bSaveToFile)
	{
		SaveAccountFile(InAccount);
	}
	return &(Pair.first)->second;
}

EErrorCode FDataBase::DeleteAccount(const FAccount& InAccount)
{
	EErrorCode ErrorCode = EErrorCode::ESuccessed;



	return ErrorCode;
}

FAccount* FDataBase::FindAccount(const FAccountName& InID)
{
	std::unordered_map<FAccountName, FAccount>::iterator It = AccountMap.find(InID);
	if (It == AccountMap.end()) { return nullptr; }

	return &It->second;
}

FAccount* FDataBase::CheckAccount(const FAccount& InAccount, EErrorCode* const OptionalOutErrorCode, const bool bSaveToFile)
{
	if (InAccount.IsEmpty())
	{
		if (OptionalOutErrorCode) { *OptionalOutErrorCode = EErrorCode::EEmptyAccount; }
		return nullptr;
	}

	FAccount* FoundAccount = FindAccount(InAccount.ID);
	if (FoundAccount == nullptr)
	{
		if (OptionalOutErrorCode) { *OptionalOutErrorCode = EErrorCode::ECanNotFoundAccount; }
		return nullptr;
	}

	if (*FoundAccount != InAccount)
	{
		if (OptionalOutErrorCode) { *OptionalOutErrorCode = EErrorCode::EAccountNotValid; }
		return nullptr;
	}

	return FoundAccount;
}



void FDataBase::SaveAccountFile(const FAccount& InAccount)
{
	const std::string UserDirectory = AccountsDirectory + "\\" + InAccount.ID;
	{
		std::string cmd = "mkdir" + UserDirectory;
		system(cmd.c_str());
	}

	// json
	{
		rapidjson::Document Doc(rapidjson::kObjectType);
		rapidjson::Value Account(rapidjson::kObjectType);

		Account.AddMember("ID", rapidjson::StringRef(InAccount.ID.data()), Doc.GetAllocator());
		Account.AddMember("Password", rapidjson::StringRef(InAccount.Password.data()), Doc.GetAllocator());
		Doc.AddMember("Account", Account, Doc.GetAllocator());

		rapidjson::StringBuffer Buffer;
		rapidjson::Writer<rapidjson::StringBuffer> Wirter(Buffer);
		Doc.Accept(Wirter);
		std::string Json(Buffer.GetString(), Buffer.GetSize());

		std::ofstream File(UserDirectory + "\\" + "Account.json");
		File << Json;
	}
}
