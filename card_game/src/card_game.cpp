//============================================================================
// Name        : card_game.cpp
// Author      : Soeren korsgaard
// Version     : rev 1.0
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <bits/stdc++.h>
#include <csignal>
using namespace std;

#define DECK_SIZE 52
#define CARD_PER_HAND 5
#define MAX_NUMBER_OF_PLAYERS 5
#define MIN_NUMBER_OF_PLAYERS 2
#define CARD_SUITS 4
#define CARD_NUMBERS 13
#define MAXIMUM_CHARS 32


void ShutDown(int signal_)
{
    cout <<"Goodbye"<<endl;
    exit(EXIT_SUCCESS);
}

class Card{
	public:
		string suits;
		string faces;
		uint16_t score;
};

class Deck{
	public:
		Deck()
		{
			CreateDeck();
		}
		void BlendCards()
		{
			random_shuffle(&deck[0],&deck[DECK_SIZE - 1]);
		}
		Card GetCard(uint8_t DeckCount)
		{
			return deck[DeckCount];
		}
	private:
		string faces[CARD_NUMBERS] = {"Ace","Deuce","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","Queen","King"};
		string suits[CARD_SUITS] = {"Hearts","Diamonds","Clubs","Spades"};
		Card deck[DECK_SIZE];
		void CreateDeck()
		{
			uint8_t i = 0;
			uint8_t j = 0;
			uint8_t deck_count = 0;
			for(i = 0 ; i < CARD_SUITS; i++)
			{
				for(j = 0 ; j < CARD_NUMBERS; j++)
				{
					deck[deck_count].suits = suits[i];
					deck[deck_count].faces = faces[j];
					deck[deck_count].score = i * j;
					deck_count++;
				}
			}
		}

};


class Player {
	public:
		void GiveName(int player_num)
		{
			cout << "Name player "<< player_num << endl;
			ws(cin);
			getline(cin,name);
			if (name.length() > MAXIMUM_CHARS)
			{
			  name.erase(MAXIMUM_CHARS);
			}
			cout << "Player " << player_num <<" is " << name<< endl;
		}
		void TakeCard(Card card, uint8_t card_number)
		{
			cards[card_number] = card;
		}
		uint16_t GetScore()
		{
			uint8_t i;
			total_score = 0;
			for(i = 0; i < CARD_PER_HAND; i++)
			{
				total_score += cards[i].score;
			}
			return total_score;
		}
		void ShowHand()
		{
			int i;
			cout <<"Player:: " << name<< endl;
			for(i = 0; i < CARD_PER_HAND; i++)
			{
				cout <<"Card number "<< i <<" Is -> " << cards[i].faces <<" " << cards[i].suits<<endl;
			}
			cout <<"Total score is : "<< GetScore()<<endl;
		}
		string GetName()
		{
			return name;
		}
	private:
		Card cards[CARD_PER_HAND];
		string name;
		uint16_t total_score;
};


class Game {       // The class
	public:
		Game()
		{
		 cout << "Welcome to the game"<<endl;
		 cout << "Add some player to the game"<<endl;
		}
		~Game()
		{
			players.clear();
		}
		void BlendCards()
		{
			deck.BlendCards();
		}
		void ShowHands()
		{
			uint8_t i;
			for(i = 0; i < players.size(); i++)
			{
				players[i].ShowHand();
			}
		}
		void AddNewPlayers()
		{
		    cout << "Enter number of players between 2 and 5 "<< endl;
		    while(!(cin >> numbers_of_players) || (numbers_of_players > MAX_NUMBER_OF_PLAYERS || numbers_of_players < MIN_NUMBER_OF_PLAYERS ))
		    {
		        cin.clear();
		        cin.ignore(numeric_limits<streamsize>::max(), '\n');
		        cout << "Invalid input.  Try again: "<< endl;
		    }
			uint8_t i;
			for(i = 0; i < numbers_of_players; i++)
			{
				player.GiveName(i+1);
				players.push_back(player);
			}
		}
		void DealCards()
		{
			uint8_t i,j;
			uint8_t card_from_stack = 0;
			for(i = 0; i < players.size(); i++)
			{
				for(j = 0; j < CARD_PER_HAND; j++)
				{
					players[i].TakeCard(deck.GetCard(card_from_stack++),j);
				}
			}
		}
		void FindWinner()
		{
			uint8_t i;
			for(i = 0; i < players.size(); i++)
			{
				if(players[i].GetScore() > highest_score)
				{
					highest_score = players[i].GetScore();
				}
			}
			for(i = 0; i < players.size(); i++)
			{
				if(players[i].GetScore() == highest_score)
				{
					cout <<endl<< "The winner is ---> " << players[i].GetName()<< endl;
					cout << "!!!END OF THE GAME!!!" << endl;
					break;
				}
			}
			players.clear();

		}

	private:
		int numbers_of_players = 0;
		Deck deck;
		Player player;
		vector<Player> players;
		uint16_t highest_score = 0;

};



int main() {

	signal(SIGINT, ShutDown);
	while(true)
	{
		Game game;
		game.AddNewPlayers();
		game.BlendCards();
		game.DealCards();
		game.ShowHands();
		game.FindWinner();
	}
	return 0;
}



