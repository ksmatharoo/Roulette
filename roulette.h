#pragma once
#include<list>
#include<string>
#include<vector>
#include<time.h>
using namespace std;

namespace Roulette {

#define PRICE_MULTIPIER 36


#define PRINT(name,value) std::cout <<name " : "<< value << std::endl;


	typedef struct _bet {
		float amount;
		std::list<uint8_t> selectedNum;
		float getBetPerNum() { return amount / selectedNum.size(); }
		//ctor
		_bet(float a, std::list<uint8_t>  l1) :amount(a), selectedNum(l1) {};

		string getSellectedNumString() {
			char buffer[1024] = { 0 };
			int size = selectedNum.size();

			string s = "{";
			for (auto a : selectedNum) {
				sprintf_s(buffer, "%d,", a);
				s += buffer;
			}
			s.resize(s.size() - 1);
			s += "}";
			return std::move(s);
		}
	}bet;


	typedef struct _user
	{
		float totalLeft;
		std::string name;
		_user(float f, std::string s) :totalLeft(f), name(s) {};

	}user;

	//its a single user machine take care of single user
	class rouletteMachine {
		user *u1;
		uint8_t finalNumber;
		float lastWinAmount;
		std::list<bet> bets;
		void init(time_t t1)
		{
			srand(t1);
		}
		void updateUserState(float winAmount, int betAmount) {
			if (0 == winAmount) {
				this->u1->totalLeft -= betAmount;
			}
			else {
				this->u1->totalLeft += winAmount;
			}
		}

	public:

		rouletteMachine(user *_u1,time_t t1) :u1(_u1) {
			std::cout << "Welcome to Roulette : " << _u1->name << std::endl;
			init(t1);
		}

		uint8_t luckyNum() { return this->finalNumber; }

		float getWonMoney() const { return lastWinAmount; }

		void setUserBets(std::list<bet> b1) { this->bets = b1; }

		std::list<bet> getLastBetListbets() const { return this->bets; };

		string getSeletedNum()
		{
			string str;
			for (auto b : bets) {
				str += b.getSellectedNumString();
			}
			return std::move(str);
		}

		void calulatePayoutandUpdateUserState()
		{
			lastWinAmount = 0; 
			float win = 0;
			for (auto bet : bets)
			{
				win = 0;
				float betPerNum = bet.getBetPerNum();
				for (auto num : bet.selectedNum) {
					if (num == this->finalNumber) {
						win += betPerNum * PRICE_MULTIPIER;
						break;
					}
				}
				updateUserState(win, bet.amount);
				lastWinAmount += win;
			}
			
		}

		//retrun const read only reference 
		user const* GetCurrentUserState()
		{
			return u1;
		}

		float GetCurrentUserMoneyState()
		{
			return u1->totalLeft;
		}

		int spin() {
			if (u1->totalLeft <= 0 || u1->totalLeft < this->getTotalBets())
				return -1;

			this->finalNumber =  std::rand() % (PRICE_MULTIPIER + 1);
			calulatePayoutandUpdateUserState();
			return finalNumber;
		}

		void increase2xAllbets() {
			for (auto &b : this->bets) {
				b.amount *= 2;
			}
		}

		float getTotalBets() const {
			float amount = 0;
			for (auto b : this->bets) {
				amount += b.amount;
			}
			return amount;
		}
	};
}