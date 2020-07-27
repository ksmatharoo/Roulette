
#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include <memory>
#include "utils.h"

BOOST_AUTO_TEST_CASE(Test_addOrder)
{
	auto list = Roulette::getNeighbours(10);

	//int *arr = new int[list.size()];
	std::unique_ptr<int[],std::default_delete<int[]>> arr(new int[list.size()]);

	std::copy(list.begin(), list.end(), arr.get());


	int expected[] = {7,8,10,11};
	
	for (int i = 0; i < list.size();i++) {
	
		BOOST_REQUIRE(arr[i] == expected[i]);

	}

}