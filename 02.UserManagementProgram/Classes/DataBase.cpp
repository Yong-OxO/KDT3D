#include "DataBase.h"
#include "LoginSession.h"

FDataBase* FDataBase::Get(const bool bDestry)
{
	static std::unique_ptr<FDataBase> Instance{new FDataBase};
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
	EErrorCode ErrorCode;

	FAccount* Account = CheckAccount(InAccount, &ErrorCode);

	if (Account == nullptr)
	{
		assert(nullptr);
		return ErrorCode;
	}

	AccountMap.erase(InAccount.ID);
	DeleteAccountFile(InAccount);

	ErrorCode = EErrorCode::ESuccessed;

	return ErrorCode;
}

EErrorCode FDataBase::CreatePlayer(const FAccount& InAccount, std::string_view InPlayerName)
{
	EErrorCode ErrorCode;
	FAccount* Account = FDataBase::Get()->CheckAccount(InAccount, &ErrorCode);
	if (Account == nullptr)	{ return ErrorCode; }

	const std::string UserDirectory = AccountsDirectory + "\\" + Account->ID;
	const std::string PlayerFile = UserDirectory + "\\" + InPlayerName.data() + ".json";

	{
		std::ifstream File(PlayerFile);
		if (File.is_open())	{ ErrorCode = EErrorCode::EDuplicateAccount; }
	}

	FPlayer NewPlayer = FPlayer(InAccount.ID, InPlayerName, 0);
	SavePlayer(&NewPlayer);

	return ErrorCode;
}

EErrorCode FDataBase::DeletePlayer(const FAccount& InAccount, std::string_view InPlayerName)
{
	EErrorCode ErrorCode;
	std::shared_ptr<FPlayer> Player = CheckPlayer(InAccount, InPlayerName, &ErrorCode);
	if (ErrorCode != EErrorCode::ESuccessed) { return ErrorCode; }

	// @TODO : 로그인중이라면 로그아웃

	std::string cmd = "del /q " + AccountsDirectory + "\\" + InAccount.ID + "\\" + InPlayerName.data() + ".json";
	system(cmd.c_str());

	ErrorCode = EErrorCode::ESuccessed;
	return ErrorCode;
}

std::shared_ptr<FPlayer> FDataBase::CheckPlayer(const FAccount& InAccount, std::string_view InPlayerName, EErrorCode* const OptionalOutErrorCode)
{
	EErrorCode ErrorCode;
	FAccount* Account = CheckAccount(InAccount, &ErrorCode);
	if (ErrorCode != EErrorCode::ESuccessed) { return nullptr; }

	const std::string UserDirectory = AccountsDirectory + "\\" + InAccount.ID;
	const std::string PlayerFile = UserDirectory + InPlayerName.data() + ".json";
	
	std::ifstream File(PlayerFile);
	if (File.is_open() == false)
	{
		if (OptionalOutErrorCode) { *OptionalOutErrorCode = EErrorCode::EPlayerNotValid; }
		return nullptr;
	}

	std::string Json;
	{
		std::string temp;
		while (std::getline(File, temp)) { Json += temp; }
		if (Json.empty())
		{
			if (OptionalOutErrorCode) { ErrorCode = EErrorCode::EPlayerNotValid; }
			return nullptr;
		}
	}

	rapidjson::Document Doc(rapidjson::kObjectType);
	Doc.Parse(Json.data());

	const bool bPlayerInfo = Doc.HasMember("PlayerInfo");
	if (bPlayerInfo == false)
	{
		assert(false);
		if (OptionalOutErrorCode) { ErrorCode = EErrorCode::EPlayerNotValid; }
		return nullptr;
	}

	std::shared_ptr<FPlayer> Player = std::make_shared<FPlayer>();
	rapidjson::Value& PlayerInfoValue = Doc["PlayerInfo"];

	if (Player->Load(PlayerInfoValue) == false)
	{
		assert(nullptr);
		if (OptionalOutErrorCode) { ErrorCode = EErrorCode::EPlayerNotValid; }
		return nullptr;
	}

	if (OptionalOutErrorCode) { *OptionalOutErrorCode = EErrorCode::ESuccessed; }

	return Player;
}

FAccount* FDataBase::FindAccount(const FAccountName& InID)
{
	std::unordered_map<FAccountName, FAccount>::iterator It = AccountMap.find(InID);
	if (It == AccountMap.end()) { return nullptr; }

	return &It->second;
}

FAccount* FDataBase::CheckAccount(const FAccount& InAccount, EErrorCode* const OptionalOutErrorCode)
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
	if (OptionalOutErrorCode) { *OptionalOutErrorCode = EErrorCode::ESuccessed; }

	return FoundAccount;
}



void FDataBase::SaveAccountFile(const FAccount& InAccount)
{
	const std::string UserDirectory = AccountsDirectory + "\\" + InAccount.ID;
	{
		std::string cmd = "mkdir " + UserDirectory;
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

void FDataBase::DeleteAccountFile(const FAccount& InAccount)
{
	// s -> 폴더 안 파일이 존재해도 강제 제거 / q -> 확인절차 무시(queit)
	std::string cmd = "rmdir /s /q " + AccountsDirectory + "\\" + InAccount.ID;
	system(cmd.c_str());
}

void FDataBase::SavePlayer(FPlayer* InPlayer)
{
	const std::string UserDirectory = AccountsDirectory + "\\" + InPlayer->GetAccountName().data();
	const std::string PalyerFile = UserDirectory + "\\" + InPlayer->GetPlayerName().data();

	// json
	{
		rapidjson::Document Doc(rapidjson::kObjectType);
		rapidjson::Value PlayerInfo(rapidjson::kObjectType);

		InPlayer->Save(PlayerInfo, Doc.GetAllocator());

		Doc.AddMember("PlayerInfo", PlayerInfo, Doc.GetAllocator());

		rapidjson::StringBuffer Buffer;
		rapidjson::Writer<rapidjson::StringBuffer> Wirter(Buffer);
		Doc.Accept(Wirter);
		std::string Json(Buffer.GetString(), Buffer.GetSize());

		std::ofstream File(PalyerFile);
		File << Json;
	}
}

FDataBase::FDataBase()
{
	std::string cmd = "mkdir " + AccountsDirectory;
	system(cmd.c_str());	

	const std::filesystem::path AccountsPath{ AccountsDirectory };
	for (auto const& It : std::filesystem::directory_iterator{ AccountsPath })
	{
		if (It.is_directory() == false)	{ continue;	}

		std::wstring Path = It.path().c_str();
		std::string AccountJsonPath(Path.begin(), Path.end());
		AccountJsonPath = AccountJsonPath + "\\" + "Account.json";

		std::ifstream File(AccountJsonPath);
		if (File.is_open() == false) { continue; }

		std::string Json;
		{
			std::string temp;
			while (std::getline(File, temp)) { Json += temp; }
			if (Json.empty()) { continue; }
		}

		rapidjson::Document Doc(rapidjson::kObjectType);
		Doc.Parse(Json.data());

		const bool bAccount = Doc.HasMember("Account");

		if (bAccount == false)
		{
			assert(nullptr);
			continue;
		}
		
		rapidjson::Value& AccountValue = Doc["Account"];
		FAccount NewAccount;
		EErrorCode ErrorCode;
		NewAccount.ID = AccountValue["ID"].GetString();
		NewAccount.Password = AccountValue["Password"].GetString();
		CreateAccount(NewAccount, &ErrorCode, false);
		if (ErrorCode != EErrorCode::ESuccessed)
		{
			assert(nullptr);
			continue;
		}
	}	
}
