// 01-11.Pool.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "Pool.h"

int main()
{
	// new
	{
		FClass* ClassInstance = new FClass;
		delete ClassInstance;
	}

	// malloc
	{
		FClass* Memory = (FClass*)malloc(sizeof(FClass));
		new(Memory) FClass();
		Memory->~FClass();
		free(Memory);
	}

	const size_t MaxCount = 100000;
	//new, delete 성능
	{
		int** Arr = new int* [MaxCount];
	}
}

