#include <iostream>
#include <array>
#include <vector>
#include <format>
#include <memory>

void Swap(int* const pInOutFirst, int* const pInOutSecond)
{
	std::cout << std::format("Swap 전 a : {}, b : {}\n", *pInOutFirst, *pInOutSecond);

	// Temp = InOutFirst(20)
	const int Temp = *pInOutFirst;

	// InOutFirst = 10(b);
	*pInOutFirst = *pInOutSecond;

	// InOutSecond = 20(Temp; a)
	*pInOutSecond = Temp;

	std::cout << std::format("Swap 후 a : {}, b : {}\n", *pInOutFirst, *pInOutSecond);
}

void SeperateOddsAndEvens(
	const std::array<int, 10>& RefInNumbers,
	std::vector<int>& RefOutOdds,
	std::vector<int>& RefOutEvens)
{
	std::cout << "Array : ";
	for (int Value : RefInNumbers)
	{
		std::cout << Value << " ";

		// 홀수 판정
		// 1 / 2: 몫:0 나머지:1 => 홀수
		// 2 / 2: 몫:0 나머지:0 => 짝수
		// 3 / 2: 몫:1 나머지:1 => 홀수
		// 4 / 2: 몫:2 나머지:0 => 짝수
		if (Value % 2 == 1) // 홀수(나머지가 1)
		{
			RefOutOdds.push_back(Value);
		}
		else if (Value % 2 == 0) // 짝수(나머지가 0)
		{
			RefOutEvens.push_back(Value);
		}
		else
		{
			// 혹시 여기 들어오면 한번 쯤 봐야겠다...
			_ASSERT(false);
		}
	}
	std::cout << "\n";

	// Odds 출력
	std::cout << "Odds : ";
	for (int i = 0; i < RefOutOdds.size(); ++i)
	{
		std::cout << RefOutOdds[i] << " ";
	}
	std::cout << "\n";

	// Evens 출력
	std::cout << "Evens: ";
	for (int i = 0; i < RefOutEvens.size(); ++i)
	{
		std::cout << RefOutEvens[i] << " ";
	}
	std::cout << "\n";
}

class Test 
{
public:
	int a = 10;

	std::unique_ptr<int> p_a = std::make_unique<int>(5);

	void Print()
	{
		std::cout << "Hello" << std::endl;
	}
};

#include <functional>
int main()
{
	Test t;
	
	void (*TestPrint)() = Test::Print;
}

