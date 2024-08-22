#pragma once
#include "Misc/Headers.h"

enum EMenuEvent : uint8_t
{
	ETerminate = 0,

	ECreateAccount,		// 1
	EDeleteAccount,		// 2
	EPrintAccount,		// 3

	ECreatePlayer,		// 4
	EDeletePlayer,		// 5
	ELogin,				// 6
	ELogout,			// 7
	EPrintLoginUsers,	// 8

	EPlayerLevelUp		// 9
};

class FEngine
{
public:
	void Run();

private:
	void Init();
	void Release();

	EMenuEvent PrintMenuAndSelectEvent();

private:
	bool bTerminated = false;
};

extern FEngine GEngine;