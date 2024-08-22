#include "LogoutTask.h"
#include "Classes/LoginSession.h"
#include "Misc/Utils.h"

FLogoutTask::FLogoutTask()
{
	std::cout << "[ ------  로그아웃  ------- ]" << std::endl;
	const FAccount Account = FUtils::MakeAccountFromUserInput();
	
	std::string CharacterName;
	std::cout << std::format("Input CharacterName: ");
	std::cin >> CharacterName;

	FLoginSession::Get()->Logout(Account, CharacterName);
}
