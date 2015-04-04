// p2.cpp
// Author: ZhangFuming/AlexChang
// Date: 2015-04-02
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
using namespace std;

struct type					// type of the return value of the function Deal 
{
	int suit;				// store the suit of one card
	int sn;					// store the serial number of one card
	double value;			// store the value of one card
};

void Shuffle(double cards[4][13]);		// Shuffle the cards
type Deal(double cards[4][13]);			// Deal out the cards
void Show(type card);					// Show the cards
void HandlePlayer(double cards[4][13]);		// Player Round and the victory and defeat judgement
void HandleAI(double cards[4][13], double total, int count);		// AI Round and the victory and defeat judgement
char Input();		// the error detection in the input

int main()
{
	double cards[4][13];		// define a two-dimensional array to represent the cards
	char choose;					// get the input
	
	srand(time(NULL));
	
	do {
		HandlePlayer(cards);			// call the Player function
		cout << "\nDo you want to continue(y/n): ";
		choose=Input();
		cout << endl;
	}
	while (choose=='y');
	
	return 0;
}

void Shuffle(double cards[4][13])
{
	int i,j;
	
	for (i=0; i<4; ++i){		// initialize the value of the cards
		for (j=0; j<13; ++j){
			if (j<10) cards[i][j]=j+1;
			else cards[i][j]=0.5;
		}
	}	
}

type Deal(double cards[4][13])
{
	int i,j;
	type card;
	
	do {						// deal out one new card
		i=rand()%4;
		j=rand()%13;
		if (cards[i][j]!=0) break;
	} while (cards[i][j]==0);		
	card.suit=i;
	card.sn=j;
	card.value=cards[i][j];
	cards[i][j]=0;
	
	return (card);
}

void Show(type card)
{ 
	switch (card.suit){
		case 0: cout << "Heart "; break;
		case 1: cout << "Spade "; break;
		case 2: cout << "Club "; break;
		default: cout << "Diamond ";
	}
	if (card.sn>=1 && card.sn<=9) cout << card.sn+1 << ' ';
	else{
		switch (card.sn){
			case 0: cout << 'A' << ' '; break;
			case 10: cout << 'J' << ' '; break;
			case 11: cout << 'Q' << ' '; break;
			default: cout << 'K' << ' ';
		}
	}
}

void HandlePlayer(double cards[4][13])
{
	double total=0.0;			// the total value of cards on hand
	int i, count=0, cardOnHand[30];		// count: the number of cards on hand, cardOnHand: the cards on hand
	char choose;				// get the input
	type temp;
	
	Shuffle(cards);				// call the Shuffle function
	cout << "Player" << endl;
	cout << "Player gets cards ";
		
	while (count<2){			// Deal out the first two cards
		temp=Deal(cards);
		Show(temp);
		total+=temp.value;
		cardOnHand[count*2]=temp.suit;		// record the cards on hand
		cardOnHand[count*2+1]=temp.sn;
		count+=1;
	}
	cout << endl << "Do you want more cards(y/n): ";
	choose=Input();
	while (choose=='y')
	{
		cout << "Get one more card: ";
		for (i=0; i<=2*count-2; i+=2){		// show the cards on hand
			temp.suit=cardOnHand[i];
			temp.sn=cardOnHand[i+1];
			Show(temp);
		}
		temp=Deal(cards);
		Show(temp);
		total+=temp.value;
		cardOnHand[count*2]=temp.suit;
		cardOnHand[count*2+1]=temp.sn;
		count+=1;
		if (total>21){
			cout << "\n\nThe player loses.\n";
			return;
		}
		cout << endl << "Do you want more cards(y/n): ";
		choose=Input();
	}
	HandleAI(cards,total,count);		// call the HandleAI function
}

void HandleAI(double cards[4][13], double total, int count)
{
	double total_AI=0.0;			// the total value of cards on AI's hand
	int i,count_AI=0, cardOnHand[30];	// count: the number of cards on AI's hand
										// cardOnHand: the cards on AI's hand
	type temp;
	
	cout << endl << "AI" << endl;
	cout << "AI gets cards ";
		
	while (count_AI<2){					// Deal out the first two cards
		temp=Deal(cards);
		Show(temp);
		total_AI+=temp.value;
		cardOnHand[count_AI*2]=temp.suit;	// record the cards on hand
		cardOnHand[count_AI*2+1]=temp.sn;
		count_AI+=1;
	}
	if (total_AI>total) {
		cout << "\n\nThe player loses.\n";
		return;
	}
	else {
		while(true){
			cout << "\nGet one more card: ";
			for (i=0; i<=2*count_AI-2; i+=2){		// show the cards on hand
				temp.suit=cardOnHand[i];
				temp.sn=cardOnHand[i+1];
				Show(temp);
			}
			temp=Deal(cards);
			Show(temp);
			total_AI+=temp.value;
			cardOnHand[count_AI*2]=temp.suit;
			cardOnHand[count_AI*2+1]=temp.sn;
			count_AI+=1;
			if (total_AI==total&&count_AI>count){
				cout << "\n\nThe player loses\n";
				return;
			}
			if (total_AI>21){
				cout << "\n\nThe player wins\n";
				return;
			}
			if (total_AI>total){
				cout << "\n\nThe player loses\n";
				return;
			}
		}	
	} 
}

char Input()
{
	string inp;		// the string to store the input
	char c;			// store the first charcter of the string
	try
	{
		cin >> inp;
		if (inp.length()>1) throw runtime_error("too long! ");		// judge if the input is too long
		c=inp[0];
		if (tolower(c)!='y' && tolower(c)!='n') throw runtime_error("not y/n! ");	// judge if the input is y/n
		return (tolower(c));
	}
	catch (runtime_error& e)
	{
		cout << "Your input is " << e.what() << "Please input y/n: ";
		return Input();		// recursion
	}
}
