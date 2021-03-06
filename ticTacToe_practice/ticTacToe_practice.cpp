// ticTacToe_practice.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//global constants
const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';

//function prototypes
void instructions();
char askYesNo(string question);
int askNumber(string question, int high, int low = 0);
char humanPiece();
char opponent(char piece);
void displayBoard(const vector<char>& board);
char winner(const vector<char>& board);
bool isLegal(const vector<char>& board, int move);
int humanMove(const vector<char>& board, char human);
int computerMove(const vector<char>& board, char computer);
void announceWinner(char winner, char computer, char human);

int main()
{
	int move;
	
	//Create an empty tic-tac-toe board
	const int NUM_SQUARES = 9;
	vector<char> board(NUM_SQUARES, EMPTY);
	
	// Display the game instructions
	instructions();

	//Determine who goes first
	char human = humanPiece();
	char computer = opponent(human);
	char turn = X;

	// Display the board
	displayBoard(board);

	// While nobody has won and it's not a tie
	while (winner(board) == NO_ONE)
	{
		if (turn == human) //If its the human's turn
		{
			move = humanMove(board, human); //Get the human's move
			board[move] = human; //Update the board with the human's move
		}
		else //Otherwise
		{
			move = computerMove(board, computer); //Calculate the computer's move
			board[move] = computer; //Update the board with the computer's move
		}

		displayBoard(board); //Display the board
		turn = opponent(turn);//Switch turns
	}
	
	//Congratulate the winner or declare a tie
	announceWinner(winner(board), computer, human);
		
		
	system("pause");
	return 0;
}

void instructions()
{
	cout << "Welcome to the ultimate man-machine showdown: Tic-Tac-Toe\n";
	cout << "---where human brain is pit against silicon processor\n\n";

	cout << "Make your move known by entering a number, 0-8. The number\n";
	cout << "corresponds to the desired position, as illustrated:\n\n";

	cout << " 0 | 1 | 2\n";
	cout << " ---------\n";
	cout << " 3 | 4 | 5\n";
	cout << " ---------\n";
	cout << " 6 | 7 | 8\n\n";

	cout << "Prepare yourself, human. The battle is about to begin.\n\n";
}

char askYesNo(string question)
{
	char response;
	do
	{
		cout << question << " (y/n): ";
		cin >> response;
	} while (response != 'y' && response != 'n');

	return response;
}

int askNumber(string question, int high, int low)
{
	int number;
	do
	{
		cout << question << " (" << low << " - " << high << "): ";
		cin >> number;
	} while (number > high || number < low);

	return number;
}

char humanPiece()
{
	char go_first = askYesNo("Do you require the first move?");
	if (go_first == 'y')
	{
		cout << "\nThen take the first move. You will need it.\n";
		return X;
	}

	else
	{
		cout << "\nYour bravery will be your undoing... I will go first.\n";
		return 0;
	}
}

char opponent(char piece)
{
	if (piece == X)
	{
		return 0;
	}
	else
	{
		return X;
	}
}

void displayBoard(const vector<char>& board)
{
	cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
	cout << "---------";
	cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
	cout << "---------";
	cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
	cout << "\n\n";
}

char winner(const vector<char>& board)
{
	//all possible winning rows
	const int WINNING_ROWS[8][3] =
	{ {0, 1, 2},
	{3, 4, 5},
	{6, 7, 8},
	{0, 3, 6},
	{1, 4, 7},
	{2, 5, 8},
	{0, 4, 8},
	{2, 4, 6} };

	const int TOTAL_ROWS = 8;

	// if any winning row has three values that are the same (and not EMPTY),
	// then we have a winner
	for (int row = 0; row < TOTAL_ROWS; ++row)
	{
		if ((board[WINNING_ROWS[row][0]] != EMPTY) &&
			(board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) &&
			(board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]]))
		{
			return board[WINNING_ROWS[row][0]];
		}
	}

	//since nobody has won, check for a tie (no empty squares left)
	if (count(board.begin(), board.end(), EMPTY) == 0)
	{
		return TIE;
	}

	// since nobody has won and it isn't a tie, the game ain't over
	return NO_ONE;
}

inline bool isLegal(int move, const vector<char>& board) 
{
	return (board[move] == EMPTY);
}

int humanMove(const vector<char>& board, char human)
{
	int move = askNumber("Where will you move?", (board.size() - 1));
	while (!isLegal(move, board))
	{
		cout << "\nThat square is already occupied, foolish human.\n";
		move = askNumber("Where will you move?", (board.size() - 1)); 
	}

	cout << "Fine...\n";

	return move;
}