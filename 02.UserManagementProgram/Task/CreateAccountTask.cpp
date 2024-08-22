#include "CreateAccountTask.h"
#include "Misc/Utils.h"
#include "Classes/DataBase.h"


FCreateAccountTask::FCreateAccountTask()
{
	std::cout << "[ ------ 계정  생성 ------- ]" << std::endl;
	const FAccount Account = FUtils::MakeAccountFromUserInput();
	EErrorCode ErrorCode;
	FAccount* NewAccount = FDataBase::Get()->CreateAccount(Account, &ErrorCode);
	FUtils::PrintSystemSuccessOrFailed(NewAccount,
		std::format("Create Account Error: {} / ID: {} / Password: {}\n", (int)ErrorCode, Account.ID, Account.Password));
}