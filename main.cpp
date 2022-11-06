#include <iostream>


void printTicTacToe(char arr[][3], int sizeX, int sizeY);
void playerX(char arr[][3]);
void playerO(char arr[][3]);
bool checkWin(char arr[][3], int sizeX, int sizeY);




int main()
{
	char winner = ' ';
	int count = 0;
	char symbols[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};


	printTicTacToe(symbols, 3, 3);


	while (true)
	{
		playerX(symbols);
		printTicTacToe(symbols, 3, 3);
		count++;
		if (checkWin(symbols,3,3))
		{
			std::cout << "the winner is X";
			return 0;
		}

		if (count == 9)
		{
			break;
		}

		playerO(symbols);
		printTicTacToe(symbols, 3, 3);
		count++;
		if (checkWin(symbols, 3, 3))
		{
			std::cout << "the winner is O";
			return 0;
		}
	}
	std::cout << "it is a tie :/";
	return 0;

	//[1].[1,2,3] , [2].[1,2,3] , [3].[1,2,3]
	//[1,2,3].[1] , [1,2,3].[2] , [1,2,3].[3]
	//[1][1] , [2][2] , [3][3]
	//[1][3] , [2][2] , [3][1]
}


void printTicTacToe(char arr[][3], int sizeX, int sizeY)
{
	std::cout << "    ";
	for (int i = 0; i < sizeX; i++)
	{
		std::cout << i + 1 << "   ";
	}
	std::cout << std::endl;

	for (int i = 0; i < sizeX; i++)
	{
		std::cout << std::endl;

		std::cout << i + 1 << "   ";
		for (int j = 0; j < sizeY; j++)
		{
			if (j == 0)
			{
				std::cout << arr[i][j];
			}
			else
			{
				std::cout << " | " << arr[i][j];

			}
		}
		std::cout << std::endl;

		if (i != sizeX - 1)
		{
			std::cout << "   ---+---+---";
		}
	}
}

void playerX(char arr[][3])
{
	std::cout << "It's X's turn. Type coridinates. Ex. \"2 3\"\n";
	int x, y;
	do
	{
		std::cin >> x >> y;
		if (arr[x - 1][y - 1] != ' ')
		{
			std::cout << "You can't place there. Try again.\n";
		}
		else
		{
			arr[x - 1][y - 1] = 'X';
			break;
		}

	} while (true);
}
void playerO(char arr[][3])
{
	std::cout << "It's O's turn. Type coridinates. Ex. \"2 3\"\n";
	int x, y;
	do
	{
		std::cin >> x >> y;
		if (arr[x - 1][y - 1] != ' ')
		{
			std::cout << "You can't place there. Try again.\n";
		}
		else
		{
			arr[x - 1][y - 1] = 'O';
			break;
		}
		
	} while (true);
}

bool checkWin(char arr[][3], int sizeX, int sizeY)
{
	for (int i = 0; i < sizeX; i++)
	{
		if (arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2] && arr[i][0] != ' ')
		{
			return true;
		}
		else if (arr[0][i] == arr[1][i] && arr[1][i] == arr[2][i] && arr[0][i] != ' ')
		{
			return true;
		}
		
	}
	if (arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2] && arr[1][1] != ' ')
	{
		return true;
	}
	else if (arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0] && arr[1][1] != ' ')
	{
		return true;
	}
	return false;



}

