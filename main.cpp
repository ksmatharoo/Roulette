#include<iostream>
#include "roulette.h"
#include "utils.h"
using namespace std;

using namespace Roulette;


int main()
{
	user u1(50, "ksingh");
	auto *game = new rouletteMachine(&u1, /*time(NULL)*/1234);

	bet b1(1, { 1,2,4,5 });
	bool bWon = false;

	//while (!bWon)
	{
		list<bet> mbets;
		mbets.push_back(b1);
		game->setUserBets(mbets);

		printf("#Iteration. #Total_Bet  #Lucky_Number!!  #Price_Won  #Wallet_Bal  #Bets\n");
		for (int i = 1; i <= 5; i++)
		{
			if (-1 == game->spin()) {
				printf("Your are out of money for this bet.\n");
				break;
			}

			printf("%d	    %f	%d		 %f	%f  %s\n", i, game->getTotalBets(),
				game->luckyNum(), game->getWonMoney(), game->GetCurrentUserMoneyState(),
				game->getSeletedNum().c_str()
			);

			//set up new bets
			std::list<uint8_t> autoBets = getNeighbours(game->luckyNum());
			std::list<bet> lastGameBets = game->getLastBetListbets();

			bet newBets(lastGameBets.begin()->amount, autoBets);
			lastGameBets.push_back(newBets);
			game->setUserBets(lastGameBets);
			//2x
			game->increase2xAllbets();
		}
		//break;
	}
	return 0;
}
