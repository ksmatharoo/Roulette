#pragma once
#include<list>

namespace Roulette {

	static uint8_t board[13][3] =
	{		0,0,0,
		//============
			1,2,3,
			4,5,6,
		//============
			7,8,9,
			10,11,12,
		//=================
			13,14,15,
			16,17,18,
		//============
			19,20,21,
			22,23,24,
		//=================
			25,26,27,
			28,29,30,
		//============
			31,32,33,
			34,35,36
	};

	std::list<uint8_t> getNeighbours(uint8_t num) {

		if (0 == num)
			return { 0,1,2,3 };

		std::list<uint8_t> l1;
		uint8_t rowIndex = num <= 3 ? 1 : num % 3 == 0 ? (num / 3) : (num / 3 + 1);
		uint8_t colIndex = ((num % 3) == 0 ? 3 : (num % 3)) - 1;

		//start of Square should always be odd for eg 1,1 3,3 5,5
		if (rowIndex % 2 != 1) { //if not odd ,make odd
			rowIndex--;
		}
		if (colIndex == 2) {
			colIndex--;
		}

		for (int i = rowIndex; i <= rowIndex + 1; i++) {
			for (int j = colIndex; j <= colIndex + 1; j++) {
				l1.push_back(board[i][j]);
			}
		}
		return l1;
	}
}
