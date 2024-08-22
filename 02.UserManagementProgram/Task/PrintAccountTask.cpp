#include "PrintAccountTask.h"
#include "Classes/DataBase.h"

FPrintAccountTask::FPrintAccountTask()
{
	system("cls");
	const std::unordered_map<FAccountName, FAccount> Account = FDataBase::Get()->GetAccounts();
	std::cout << "[ ------ 계정  정보 ------- ]" << std::endl;
	for (const auto& It : Account) // const &?
	{
		std::cout << std::format("-> ID: {}, Password: {}\n", It.second.ID, It.second.Password);
	}
	std::cout << "[ ------------------------- ]" << std::endl;
}