#include "PlayerLevelUpTask.h"
#include "Classes/LoginSession.h"
#include "Misc/Utils.h"

FPlayerLevelUpTask::FPlayerLevelUpTask()
{
	std::cout << "[ ------   레벨업   ------- ]" << std::endl;

	FAccount Account = FUtils::MakeAccountFromUserInput();
	std::string CharacterName;
	std::cout << std::format("Input CharacterName: ");
	std::cin >> CharacterName;

	EErrorCode ErrorCode;
	FPlayer* Player = FLoginSession::Get()->IsLogin(Account.ID, CharacterName);
	Player->LevelUp();
}
