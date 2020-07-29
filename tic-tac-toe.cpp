#include <bits/stdc++.h>
using namespace std;

char lehar[3][3];

struct move
{
	int r , c;
};

char p='X';
char o='O';

int pendmove(char lehar[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if(lehar[i][j]=='_')
				return 1;
		}
	}
	return 0;
}

int eval(char lehar[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		if(lehar[i][0]==lehar[i][1] and lehar[i][1]==lehar[i][2] and lehar[i][1]=='X')
			return 10;
		if(lehar[i][0]==lehar[i][1] and lehar[i][1]==lehar[i][2] and lehar[i][1]=='O')
			return -10;
	}
	for (int i = 0; i < 3; i++)
	{
		if(lehar[0][i]==lehar[1][i] and lehar[1][i]==lehar[2][i] and lehar[2][i]=='X')
			return 10;
		if(lehar[0][i]==lehar[1][i] and lehar[1][i]==lehar[2][i] and lehar[2][i]=='O')
			return -10;
	}
	if(lehar[0][0]==lehar[1][1] and lehar[1][1]==lehar[2][2] and lehar[2][2]=='X')
		return 10;
	if(lehar[0][0]==lehar[1][1] and lehar[1][1]==lehar[2][2] and lehar[2][2]=='O')
		return -10;
	if(lehar[2][0]==lehar[1][1] and lehar[1][1]==lehar[0][2] and lehar[2][0]=='X')
		return 10;
	if(lehar[2][0]==lehar[1][1] and lehar[1][1]==lehar[0][2] and lehar[2][0]=='O')
		return -10;

	return 0;
}

int minmax(char lehar[3][3], int d, bool im)
{
	int score = eval(lehar);
	if(score == 10)
		return 10;
	if(score == -10)
		return -10;

	if(pendmove(lehar)==0)
		return 0;

	if(im)
	{
		int b= -100000000;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if(lehar[i][j]=='_')
				{
					lehar[i][j]=p;
					b=max(b,minmax(lehar,d+1, !im));
					lehar[i][j]='_';
				}				
			}
		}
		return b;
	}
	else
	{
		int b= 100000000;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if(lehar[i][j]=='_')
				{
					lehar[i][j]=o;
					b=min(b,minmax(lehar,d+1, !im));
					lehar[i][j]='_';
				}				
			}
		}
		return b;	
	}
}

move bestmove(char lehar[3][3])
{
	int bestval= -100000000;
	move bestMove;
	bestMove.r = -1;
	bestMove.c = -1;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if(lehar[i][j]=='_')
			{
				lehar[i][j] = p;
				int tmp = minmax(lehar , 0 , false);
				lehar[i][j]='_';
				if(tmp>bestval)
				{
					bestMove.r=i;
					bestMove.c=j;
					bestval=tmp;
				}
			}
		}
	}
	return bestMove;
}

int main()
{
	while(true)
	{
		cout << "Welcome to Tic-Tac-Toe by Leharm , Lehar Mittal. Enter N for new game or any other key for exiting." << endl;
		char tm;
		cin >> tm;
		if(tm=='N' or tm=='n')
		{
			for(int i=0; i<3 ; i++)
				for(int j=0; j<3 ; j++)
					lehar[i][j]='_';
			cout << "Simple rules , enter row no. and column no. respectively for your choice , you are O , i am X , so lets play, choose your first entry." << endl;
			while(pendmove(lehar))
			{
				int row , col, testing;
				cin >> row >> col;
				while(lehar[row-1][col-1]!='_')
				{
					cout << "Wrong Move. You can't overwrite me. Re-enter your move." << endl;
					cout << lehar[0][0] << "|" << lehar[0][1] << "|" << lehar[0][2] << endl << lehar[1][0] << "|" << lehar[1][1] << "|" << lehar[1][2] << endl << lehar[2][0] << "|" << lehar[2][1] << "|" << lehar[2][2] << endl;
					cin >> row >> col;
				}
				lehar[row-1][col-1]=o;
				cout << lehar[0][0] << "|" << lehar[0][1] << "|" << lehar[0][2] << endl << lehar[1][0] << "|" << lehar[1][1] << "|" << lehar[1][2] << endl << lehar[2][0] << "|" << lehar[2][1] << "|" << lehar[2][2] << endl;
				testing = eval(lehar);
				if(testing<0)
				{
					cout << "You won!" << endl;
					break;
				}
				move mv = bestmove(lehar);
				lehar[mv.r][mv.c]=p;
				cout << "Now my move." << endl;
				cout << lehar[0][0] << "|" << lehar[0][1] << "|" << lehar[0][2] << endl << lehar[1][0] << "|" << lehar[1][1] << "|" << lehar[1][2] << endl << lehar[2][0] << "|" << lehar[2][1] << "|" << lehar[2][2] << endl;
				testing = eval(lehar);
				if(testing > 0)
				{
					cout << "I won , you loose!" << endl;
					break;
				}
			}
			if(eval(lehar)==0)
				cout << "OOPs , yeh toh draw ho gya , chalo ek aur , ISM hai , matiyaana hi toh hai." << endl;
		}
		else
			return 0;
	}
}
