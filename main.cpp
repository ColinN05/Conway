#include <iostream>
#include <string>
#include <fstream>

static const unsigned int board_size = 30;
static int board[board_size][board_size] = {};

void SetBoardState(const std::string& filename)
{
	std::ifstream file(filename);
	std::string line;
	std::string entry;
	int i = 0;
	while (getline(file, line))
	{
		int j = 0;
		while (getline(file, entry, ' '))
		{
			board[i][j] = std::stoi(entry);
			j++;		
		}
		i++;
	}	
}

void DisplayBoard()
{
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
			std::cout << board[i][j] << ' ';// ?"@@" : "``");
		std::cout << '\n';
	}
	std::cout << '\n';
}

void UpdateBoard()
{
	int board_copy[board_size][board_size];
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
			board_copy[i][j] = board[i][j];
	}
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			int neighbor_count = 0;
			for (int dx : {-1,0,1})
			{
				for (int dy : {-1, 0 , 1})
				{
					if (!(dx == 0 && dy == 0))
					{
						int x = i + dx;
						int y = j + dy;	
						if (!(x < 0 || y < 0 || x > board_size - 1 || y > board_size - 1))
						{
						
							if (board[x][y])
							{
								neighbor_count++;
							}
						}
					}
				}
			}
			if (neighbor_count == 2 || neighbor_count == 3) {board_copy[i][j] = board[i][j];}
			if (neighbor_count == 3) {board_copy[i][j] = 1;}
			if (neighbor_count > 3 || neighbor_count < 2) {board_copy[i][j] = 0;}
		} 
	}
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
			board[i][j] = board_copy[i][j];
	}
}


int main()
{
	
	board[1][1] = 1;
	board[2][2] = 1;
	board[2][3] = 1;
	board[1][3] = 1;
	board[0][3] = 1;
	SetBoardState("gliderboard.txt");	


	while (true)
	{
		UpdateBoard();
		DisplayBoard();
		std::cin.get();
	}

	return 0;
}