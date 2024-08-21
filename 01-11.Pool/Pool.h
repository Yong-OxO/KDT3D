#pragma once
#include <boost/pool/pool.hpp>
#include <chrono>
#include <boost/pool/object_pool.hpp>
#include <iostream>

class FClass
{
public:
	FClass()
	{
		std::cout << __FUNCTION__ << std::endl;
	}
	~FClass()
	{
		std::cout << __FUNCTION__ << std::endl;
	}
};

class FMemoryPool
{
public:
	FMemoryPool(const size_t InChunkSize,
		const size_t InChunkCount)

	{

	}


};