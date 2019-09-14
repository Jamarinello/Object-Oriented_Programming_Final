// File: Cardtrick.cpp
// Programmer: Joseph Marinello
// Date: October 28th, 2018
// Course: COP 2931*
// Purpose: Write a program that performs a cardtrick. The program will create a random deck of cards, deal them out, pick them up, and determine the secret card.


#include <iostream>
#include <iomanip>

using namespace std;

// Function prototypes
void BuildDeck(int deck[], const int size);
void PrintDeck(int deck[], const int size);
void PrintCard(int card);
void Deal(int deck[], int play[][3]);
void PickUp(int deck[], int play[][3], int column);
void SecretCard(int deck[]);
char ChangeCaps(char *ptr);


int main()
{
	// DECLARE AND INITIALIZE VARIABLES
	int column = 0, i = 0;
	int PlayAgain = 0;
	int SeeDeck = 0;
	char name[25];
	char *ptr = NULL;

	// DECLARE 52 ELEMENT ARRAY OF INTEGERS TO USE AS DECK OF CARDS
	int deck[52] = { 0 };

	// DECLARE A 7 BY 3 ARRAY TO RECEIVE CARDS DEALT TO DO THE TRICK
	int play[7][3] = { 0 };

	// GENERATE A RANDOM SEED FOR THE RANDOM NUMBER GENERATOR
	srand(time(0));

	// OPENING MESSAGE. ASK PLAYER FOR THEIR NAME.
	cout << "Hello, I am HoudiniTron 5000 and I would like to perform a card trick for you." << endl << "What is your name?" << endl;
	cout << ": "; cin >> name;

	// MAKE SURE THE FIRST LETTER IN THEIR NAME IS CAPITALIZED
	ptr = name;
	ChangeCaps(name);
	cout << endl << "It is nice to meet you, " << name << endl << endl;


	do {
		// BUILD THE DECK
		BuildDeck(deck, 52);

		// ASK IF PLAYER WANTS TO SEE THE DECK
		cout << endl << endl << "Before I begin, would you like to see the deck?" << endl;
		cout << "1 - Yes | 2 - No" << endl;
		cout << ": "; cin >> SeeDeck;
		cout << "_____________________________________________________________________________";

		if (SeeDeck == 1)
		{
			cout << endl;
			PrintDeck(deck, 52);

			cout << "-----------------------------------------------------------------------------" << endl;
			cout << endl << "I will begin by laying the cards out in three columns." << endl;
			cout << "You will identify a single card from any column and keep its identity secret." << endl;
			cin.get(); cout << endl << "Press Enter to Continue" << endl;
			cin.get();
		}
		else if (SeeDeck == 2)
		{
			cout << endl << endl << "Very well, Lets jump right into my trick." << endl;
			cout << endl << "I will begin by laying the cards out in three columns." << endl;
			cout << "You will identify a single card from any column and keep its identity secret." << endl;
			cin.get(); cout << endl << "Press Enter to Continue" << endl;
			cin.get();
		}

		// BEGIN THE CARD-TRICK LOOP
		for (i = 0; i < 3; i++)
		{
			cout << endl << endl;

			// BEGIN BY CALLING THE 'DEAL' FUNCTION
			Deal(deck, play);

			do
			{
				// ASK PLAYER TO PICK A CARD AND SAY WHAT COLUMN IT IS IN
				cout << endl << "Which column is your card in (0, 1, or 2)?: ";
				cin >> column;
				cout << endl << "Your card is in column " << column << endl;
				cout << "_____________________________________________________________________________";
			} while (column < 0 || column > 2); // ERROR CHECKING FOR ENTERING COLUMN

			// CALL THE 'PICKUP' FUNCTION TO PICK UP THE COLUMNS, THE SELECTED COLUMN BEING SECOND
			PickUp(deck, play, column);
		}

		cout << endl << endl << "Ahah! I know exactly where your card is hiding." << endl;
		// DISPLAY THE TOP 10 CARDS, THEN REVEAL THE SECRET CARD
		SecretCard(deck);

		//ASK IF THE PLAYER WANTS TO PLAY AGAIN
		cout << name << ", would you like to play again (1 - yes | 0 - no)? ";
		cin >> PlayAgain;
	} while (PlayAgain == 1);

	// EXITING MESSAGE
	cout << endl << endl << "Thank you for playing the card trick!" << endl;

	cin.get();
}


// FUNCTIONS
void BuildDeck(int deck[], const int size)
{
	int used[52] = { 0 };
	int card = 0, i = 0;

	// GENERATE CARDS UNTIL THE DECK IS FULL OF INTEGERS
	while (i < size)
	{
		// GENERATE A RANDOM NUMBER BETWEEN 0 AND 51
		card = rand() % 52;

		/* CHECK USED ARRAY AT POSITION OF THE CARD. IF 0, ADD THE CARD AND SET THE USED LOCATION TO 1. IF 1, GENERATE ANOTHER NUMBER */
		if (used[card] == 0)
		{
			used[card] = 1;
			deck[i] = card;
			i++;
		}
	}
	return;
}

void PrintCard(int card)
{
	int rank = 0;
	int suit = 0;

	rank = card % 13;
	suit = card / 13;

	// DETERMINE THE RANK OF THE CARD AND PRINT IT OUT
	switch (rank)
	{
	case 0:
		cout << "  Ace";
		break;
	case 1:
		cout << " King";
		break;
	case 2:
		cout << "Queen";
		break;
	case 3:
		cout << " Jack";
		break;
	case 4:
		cout << "   10";
		break;
	case 5:
		cout << "    9";
		break;
	case 6:
		cout << "    8";
		break;
	case 7:
		cout << "    7";
		break;
	case 8:
		cout << "    6";
		break;
	case 9:
		cout << "    5";
		break;
	case 10:
		cout << "    4";
		break;
	case 11:
		cout << "    3";
		break;
	case 12:
		cout << "    2";
		break;

	default:
		cout << setw(5) << rank;
	}

	// DETERMINE THE SUIT OF THE CARD AND PRINT IT OUT
	switch (suit)
	{
	case 0:
		cout << " of Clubs    ";
		break;
	case 1:
		cout << " of Hearts   ";
		break;
	case 2:
		cout << " of Diamonds ";
		break;
	case 3:
		cout << " of Spades   ";
		break;

	default:
		cout << setw(13) << suit;
	}
	return;
}

void Deal(int deck[], int play[][3])
{
	int row = 0, col = 0, card = 0;

	/* DEAL CARDS BY PASSING ADDRESSES OF CARD VALUES FROM THE DECK ARRAY TO THE PLAY ARRAY */
	cout << endl;
	cout << "         Column 0		Column 1	       Column 2" << endl;
	cout << "===========================================================================" << endl;

	for (int row = 0; row < 7; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			play[row][col] = deck[card]; cout << right << setw(10);
			PrintCard(deck[card]);
			card++;
		}
		cout << endl;
	}
	return;
}

void PickUp(int deck[], int play[][3], int column)
{
	int row = 0;
	int card = 0;
	int first = 0;
	int last = 0;

	switch (column)
	{
	case 0:
		first = 1;
		last = 2;
		break;
	case 1:
		first = 0;
		last = 2;
		break;
	case 2:
		first = 0;
		last = 1;
		break;
	}

	for (row = 0; row < 7; row++)
	{
		deck[card] = play[row][first];
		card++;
	}

	for (row = 0; row < 7; row++)
	{
		deck[card] = play[row][column];
		card++;
	}

	for (row = 0; row < 7; row++)
	{
		deck[card] = play[row][last];
		card++;
	}

	return;
}

void PrintDeck(int deck[], const int size)
{
	for (int i = 0; i < size; i++)
	{
		PrintCard(deck[i]); cout << endl;
	}
}

char ChangeCaps(char *ptr)
{
	if (*ptr >= 'a' && *ptr <= 'z')
	{
		*ptr = *ptr - ('a' - 'A');
	}

	return *ptr;
}

void SecretCard(int deck[])
{
	int card = 0;
	cout << endl << "Finding secret card..." << endl;
	for (card = 0; card < 10; card++)
	{
		PrintCard(deck[card]);
		cout << endl;
	}
	cout << endl << "Your secret card is the ";
	PrintCard(deck[card]);
	cout << endl << endl;
	return;
}