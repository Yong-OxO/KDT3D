#include "DeletePlayer.h"
#include "Classes/DataBase.h"
#include "Misc/Utils.h"


FDeletePlayer::FDeletePlayer()
{
	std::cout << "[ ------ 캐릭터삭제 ------- ]" << std::endl;

	FAccount Account = FUtils::MakeAccountFromUserInput();

	FDataBase* DataBase = FDataBase::Get();
	EErrorCode ErrorCode;

	std::string CharacterName;
	std::cout << std::format("Input CharacterName: ");
	std::cin >> CharacterName;

	{

	}


}