#pragma once
#include <iostream>
enum EErrorCode : uint8_t
{
	ESuccessed,				// 0
	EUnknown,				// 1
	EEmptyAccount,			// 2
	EDuplicateAccount,		// 3
	ECanNotFoundAccount,	// 4
	EAccountNotValid,		// 5

	ENoLogin,				// 6
	EDuplicatePlayerName,	// 7
	EPlayerNotValid,		// 8
};