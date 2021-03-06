// maximizeDistanceToClosestData.cpp : Defines the entry point for the console application.
//

// Есть вектор данных из 0 и 1. 
// Нужно найти место с самым плохим распределением, и вывести индекс для вставки 1 равноудаленно от других значений.
// Например [1,0,0,0,0,0,0,0,1,0,1] - результат 4. после вставки получится вектор [1,0,0,0,1,0,0,0,1,0,1].

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <exception>
#include <iterator>

using std::cout;
using std::cerr;
using std::vector;
using std::exception;
using std::logic_error;

template <typename It>
void maximizeDist( It begin, It end, int& whereToEmplace)
{	
	// if vector is empty
	if (begin == end) { throw logic_error("Begin equal to end!"); }

	if (	(end - begin == 1) || 
			(end - begin == 2 && *begin != *(begin + 1))) {
		cerr << "Nothing to emplace" << std::endl;
		return;
	}

	int repeatingElemValue = *begin;

	// length of worse allocation LENGTH over all/till now
	size_t overAllWorseLength = 0;
	size_t tillNowWorseLength = 0;

	// till now/over all begin position of worse allocation
	size_t tillNowBeginAllocPosition = 0;
	size_t overAllAllocBeginPosition = 0;

	It currPos = begin;
	for (currPos += 1; currPos != end; ++currPos) {

		if (*currPos != repeatingElemValue) {

			repeatingElemValue = *currPos;
			tillNowWorseLength = 1;
			tillNowBeginAllocPosition = currPos - begin;

		} else {

			++tillNowWorseLength;

		}

		if (tillNowWorseLength > overAllWorseLength) {

			overAllWorseLength = tillNowWorseLength;
			overAllAllocBeginPosition = tillNowBeginAllocPosition;

		}

	}

	whereToEmplace = overAllAllocBeginPosition + ( overAllWorseLength / 2 );

}

int main()
{
	//vector<int> data = { 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1 };
	vector<int> data = {1};
	int result	= 0;
	int constexpr WHAT_TO_EMPLACE = 1;

	typedef vector<int>::const_iterator constIt;
	constIt dataBegin	= data.begin();
	constIt dataEnd		= data.end();

	try {

		maximizeDist(dataBegin, dataEnd, result);
		data.at(result) = WHAT_TO_EMPLACE;
		cout << result << "\n";

	}

	catch (const exception& ex) {

		cerr << ex.what();

	}

	getchar();
}

