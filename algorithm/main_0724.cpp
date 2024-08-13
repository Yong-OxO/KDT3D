#include <iostream>
#include <array>
#include <vector>
#include <format>
#include <memory>


class Test1
{
public:
	virtual void Print()
	{
		std::cout << "This is Parent" << std::endl;
	}
};

class Test2 : public Test1
{
public:
	virtual void Print() override
	{
		std::cout << "This is Child" << std::endl;
	}
};

class Test3 : public Test2
{
public:
	virtual void Print() override
	{
		std::cout << "This is Child Child" << std::endl;
	}
};

#include <functional>
int main()
{
	
}

