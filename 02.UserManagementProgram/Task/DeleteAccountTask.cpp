#include "DeleteAccountTask.h"
#include "Misc/Utils.h"
#include "Classes/DataBase.h"

FDeleteAccountTask::FDeleteAccountTask()
{
	std::cout << "[ ------ 회원  탈퇴 ------- ]" << std::endl;
	const FAccount Account = FUtils::MakeAccountFromUserInput();
	FDataBase* DataBase = FDataBase::Get();
	{
		EErrorCode ErrorCode;
		FAccount* Result = DataBase->CheckAccount(Account, &ErrorCode);
		if (ErrorCode != EErrorCode::ESuccessed)
		{
			FUtils::PrintSystemSuccessOrFailed(ErrorCode == EErrorCode::ESuccessed,
				std::format("Delete Account Error: {} / ID: {} / Password: {}\n", (int)ErrorCode, Account.ID, Account.Password));
			return;
		}
	}

	// @TODO : 로그인상태라면 로그아웃 후 회원 탈퇴

	{
		EErrorCode ErrorCode = DataBase->DeleteAccount(Account);
		FUtils::PrintSystemSuccessOrFailed(ErrorCode == EErrorCode::ESuccessed,
			std::format("Delete Account Error: {} / ID: {} / Password: {}\n", (int)ErrorCode, Account.ID, Account.Password));
	}
}
