// p2.cpp
// Author: ZhangFuming/AlexChang
// Date: 2015-04-02
// This version of the program meets the requirements.
// However there is no annotation.
// I'll add annotation tomorrow.
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
using namespace std;

struct type
{
	int suit;
	int sn;
	double value;
};

void Shuffle(double cards[4][13]);
type Deal(double cards[4][13]);
void Show(type card);
void Player(double cards[4][13]);
void AI(double cards[4][13], double total, int count);
char Input();


int main()
{
	double cards[4][13];
	char judge;
	
	srand(time(NULL));
	
	do {
		Player(cards);
		cout << "\nDo you want to continue(y/n): ";
		judge=Input();
		cout << endl;
	}
	while (judge=='y');

	
	return 0;
}

void Shuffle(double cards[4][13])
{
	int i,j;
	
	for (i=0; i<4; ++i){
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
	
	do {
		i=rand()%4;
		j=rand()%13;
		if (cards[i][j]!=0) break;
	} while (cards[i][j]==0);
	card.value=cards[i][j];
	cards[i][j]=0;
	card.suit=i;
	card.sn=j;
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

void Player(double cards[4][13])
{
	double total=0;
	int i,count=0, array[30], return_y;
	char choose;
	type temp;
	
	Shuffle(cards);
	cout << "Player" << endl;
	cout << "Player gets cards ";
		
	while (count<2){
		temp=Deal(cards);
		Show(temp);
		total+=temp.value;
		array[count*2]=temp.suit;
		array[count*2+1]=temp.sn;
		count+=1;
	}
	cout << endl << "Do you want more cards(y/n): ";
	choose=Input();
	while (choose=='y')
	{
		cout << "Get one more card: ";
		for (i=0; i<=2*count-2; i+=2){
			temp.suit=array[i];
			temp.sn=array[i+1];
			Show(temp);
		}
		temp=Deal(cards);
		Show(temp);
		total+=temp.value;
		array[count*2]=temp.suit;
		array[count*2+1]=temp.sn;
		count+=1;
		if (total>21){
			cout << "\n\nThe player loses.\n";
			return;
		}
		cout << endl << "Do you want more cards(y/n): ";
		choose=Input();
	}
	if (choose='n') AI(cards,total,count);
}

void AI(double cards[4][13], double total, int count)
{
	double total_AI=0;
	int i,count_AI=0, array[30];
	type temp;
	
	cout << endl << "AI" << endl;
	cout << "AI gets cards ";
		
	while (count_AI<2){
		temp=Deal(cards);
		Show(temp);
		total_AI+=temp.value;
		array[count_AI*2]=temp.suit;
		array[count_AI*2+1]=temp.sn;
		count_AI+=1;
	}
	if (total_AI>total) {
		cout << "\n\nThe player loses.\n";
		return;
	}
	else {
		while(true){
			cout << "\nGet one more card: ";
			for (i=0; i<=2*count_AI-2; i+=2){
				temp.suit=array[i];
				temp.sn=array[i+1];
				Show(temp);
			}
			temp=Deal(cards);
			Show(temp);
			total_AI+=temp.value;
			array[count_AI*2]=temp.suit;
			array[count_AI*2+1]=temp.sn;
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
	string inp;
	char c;
	try
	{
		cin >> inp;
		if (inp.length()>1) throw runtime_error("too long! ");
		c=inp[0];
		if (tolower(c)!='y' && tolower(c)!='n') throw runtime_error("not y/n! ");
		return (tolower(c));
	}
	catch (runtime_error& e)
	{
		cout << "Your input is " << e.what() << "Please input y/n: ";
		return Input();
	}
}
